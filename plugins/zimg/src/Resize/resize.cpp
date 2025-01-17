#include <algorithm>
#include <cstddef>
#include <cstdint>
#include "Common/cpuinfo.h"
#include "Common/except.h"
#include "Common/pixel.h"
#include "Common/plane.h"
#include "resize.h"
#include "resize_impl.h"

namespace zimg {;
namespace resize {;

Resize::Resize(const Filter &f, int src_width, int src_height, int dst_width, int dst_height,
               double shift_w, double shift_h, double subwidth, double subheight, CPUClass cpu)
try :
	m_src_width{ src_width },
	m_src_height{ src_height },
	m_dst_width{ dst_width },
	m_dst_height{ dst_height },
	m_skip_h{ src_width == dst_width && shift_w == 0.0 && subwidth == src_width },
	m_skip_v{ src_height == dst_height && shift_h == 0.0 && subheight == src_height },
	m_impl{ create_resize_impl(f, src_width, src_height, dst_width, dst_height, shift_w, shift_h, subwidth, subheight, cpu) }
{
} catch (const std::bad_alloc &) {
	throw ZimgOutOfMemory{};
}

size_t Resize::max_frame_size(PixelType type) const
{
	int alignment = type == PixelType::FLOAT ? AlignmentOf<float>::value : AlignmentOf<uint16_t>::value;

	size_t aligned_src_width = align(m_src_width, alignment);
	size_t aligned_src_height = align(m_src_height, alignment);
	size_t aligned_dst_width = align(m_dst_width, alignment);
	size_t aligned_dst_height = align(m_dst_height, alignment);

	return std::max(aligned_src_width, aligned_dst_width) * std::max(aligned_src_height, aligned_dst_height);
}

size_t Resize::tmp_size(PixelType type) const
{
	size_t size = 0;

	// Need temporary buffer to hold the partially scaled image.
	if (!m_skip_h && !m_skip_v)
		size += max_frame_size(type);

	// Need a line buffer to store cached accumulators.
	if (type == PixelType::WORD && !m_skip_v)
		size += m_src_width * 4;

	return size;
}

void Resize::invoke_impl_h(const ImagePlane<const void> &src, const ImagePlane<void> &dst, void *tmp) const
{
	switch (src.format().type) {
	case PixelType::WORD:
		m_impl->process_u16_h(plane_cast<const uint16_t>(src), plane_cast<uint16_t>(dst), (uint16_t *)tmp);
		break;
	case PixelType::HALF:
		m_impl->process_f16_h(plane_cast<const uint16_t>(src), plane_cast<uint16_t>(dst), (uint16_t *)tmp);
		break;
	case PixelType::FLOAT:
		m_impl->process_f32_h(plane_cast<const float>(src), plane_cast<float>(dst), (float *)tmp);
		break;
	default:
		throw ZimgUnsupportedError{ "only WORD, HALF, and FLOAT are supported for resize" };
	}
}

void Resize::invoke_impl_v(const ImagePlane<const void> &src, const ImagePlane<void> &dst, void *tmp) const
{
	switch (src.format().type) {
	case PixelType::WORD:
		m_impl->process_u16_v(plane_cast<const uint16_t>(src), plane_cast<uint16_t>(dst), (uint16_t *)tmp);
		break;
	case PixelType::HALF:
		m_impl->process_f16_v(plane_cast<const uint16_t>(src), plane_cast<uint16_t>(dst), (uint16_t *)tmp);
		break;
	case PixelType::FLOAT:
		m_impl->process_f32_v(plane_cast<const float>(src), plane_cast<float>(dst), (float *)tmp);
		break;
	default:
		throw ZimgUnsupportedError{ "only WORD, HALF, and FLOAT are supported for resize" };
	}
}

void Resize::process(const ImagePlane<const void> &src, const ImagePlane<void> &dst, void *tmp) const
{
	PixelType type = src.format().type;
	int pxsize = pixel_size(type);

	if (m_skip_h && m_skip_v) {
		copy_image_plane(src, dst);
	} else if (m_skip_h) {
		invoke_impl_v(src, dst, tmp);
	} else if (m_skip_v) {
		invoke_impl_h(src, dst, tmp);
	} else {
		double xscale = (double)m_dst_width / (double)m_src_width;
		double yscale = (double)m_dst_height / (double)m_src_height;

		// Downscaling cost is proportional to input size, whereas upscaling cost is proportional to output size.
		// Horizontal operation is roughly twice as costly as vertical operation for SIMD cores.
		double h_first_cost = std::max(xscale, 1.0) * 2.0 + xscale * std::max(yscale, 1.0);
		double v_first_cost = std::max(yscale, 1.0)       + yscale * std::max(xscale, 1.0) * 2.0;

		char *tmp1 = (char *)tmp;
		char *tmp2 = tmp1 + max_frame_size(type) * pixel_size(type);

		if (h_first_cost < v_first_cost) {
			int tmp_stride = align(m_dst_width, ALIGNMENT / pxsize);
			ImagePlane<void> tmp_plane{ tmp1, m_dst_width, m_src_height, tmp_stride, type };

			invoke_impl_h(src, tmp_plane, tmp2);
			invoke_impl_v(tmp_plane, dst, tmp2);
		} else {
			int tmp_stride = align(m_src_width, ALIGNMENT / pxsize);
			ImagePlane<void> tmp_plane{ tmp1, m_src_width, m_dst_height, tmp_stride, type };

			invoke_impl_v(src, tmp_plane, tmp2);
			invoke_impl_h(tmp_plane, dst, tmp2);
		}
	}
}

} // namespace resize
} // namespace zimg
