/*****************************************************************************

        TransOpPow.h
        Author: Laurent de Soras, 2015

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (fmtcl_TransOpPow_HEADER_INCLUDED)
#define	fmtcl_TransOpPow_HEADER_INCLUDED

#if defined (_MSC_VER)
	#pragma warning (4 : 4250)
#endif



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "fmtcl/TransOpInterface.h"



namespace fmtcl
{



class TransOpPow
:	public TransOpInterface
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	explicit       TransOpPow (bool inv_flag, double p_i, double alpha = 1, double val_max = 1);
	virtual        ~TransOpPow () {}

	// TransOpInterface
	virtual double operator () (double x) const;
	virtual double get_max () const { return (_val_max); }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	const bool     _inv_flag;
	const double   _p_i;
	const double   _alpha;
	const double   _p;
	const double   _val_max;	// linear



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               TransOpPow ();
	               TransOpPow (const TransOpPow &other);
	TransOpPow &   operator = (const TransOpPow &other);
	bool           operator == (const TransOpPow &other) const;
	bool           operator != (const TransOpPow &other) const;

};	// class TransOpPow



}	// namespace fmtcl



//#include "fmtcl/TransOpPow.hpp"



#endif	// fmtcl_TransOpPow_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
