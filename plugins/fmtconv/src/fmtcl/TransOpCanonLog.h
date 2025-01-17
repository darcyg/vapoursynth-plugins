/*****************************************************************************

        TransOpCanonLog.h
        Author: Laurent de Soras, 2015

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (fmtcl_TransOpCanonLog_HEADER_INCLUDED)
#define	fmtcl_TransOpCanonLog_HEADER_INCLUDED

#if defined (_MSC_VER)
	#pragma warning (4 : 4250)
#endif



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "fmtcl/TransOpInterface.h"



namespace fmtcl
{



class TransOpCanonLog
:	public TransOpInterface
{

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	explicit       TransOpCanonLog (bool inv_flag);
	virtual        ~TransOpCanonLog () {}

	// TransOpInterface
	virtual double operator () (double x) const;
	virtual double get_max () const { return (8.00903); }



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	const bool     _inv_flag;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               TransOpCanonLog ();
	               TransOpCanonLog (const TransOpCanonLog &other);
	TransOpCanonLog &
	               operator = (const TransOpCanonLog &other);
	bool           operator == (const TransOpCanonLog &other) const;
	bool           operator != (const TransOpCanonLog &other) const;

};	// class TransOpCanonLog



}	// namespace fmtcl



//#include "fmtcl/TransOpCanonLog.hpp"



#endif	// fmtcl_TransOpCanonLog_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
