/*****************************************************************************

        ArrayAlign.h
        Author: Laurent de Soras, 2010

Template parameters:

- T: Element type
- LEN: Number of elements, > 0
- AL: Desired memory alignement, in bytes. > 0 and must a power of 2.

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#if ! defined (fstb_ArrayAlign_HEADER_INCLUDED)
#define	fstb_ArrayAlign_HEADER_INCLUDED

#if defined (_MSC_VER)
	#pragma once
	#pragma warning (4 : 4250)
#endif



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <climits>
#include <cstdint>



namespace fstb
{



template <typename T, long LEN, long AL>
class ArrayAlign
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	typedef	T	Element;

	enum {         NBR_ELT   = LEN };
	enum {         ALIGNMENT = AL  };

	               ArrayAlign ();
	               ArrayAlign (const ArrayAlign &other);
	               ~ArrayAlign ();

	ArrayAlign &   operator = (const ArrayAlign &other);

	inline const Element &
	               operator [] (long pos) const;
	inline Element &
	               operator [] (long pos);

	static inline long
	               size ();
	static inline long
	               length ();
	static inline long
	               get_alignment ();



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	enum {         ELT_SIZE_BYTE = sizeof (Element) * CHAR_BIT / 8	};

	uint8_t        _data [NBR_ELT * ELT_SIZE_BYTE + ALIGNMENT - 1];
	Element *      _data_ptr;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	bool           operator == (const ArrayAlign &other) const;
	bool           operator != (const ArrayAlign &other) const;

};	// class ArrayAlign



}	// namespace fstb



#include "fstb/ArrayAlign.hpp"



#endif	// fstb_ArrayAlign_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
