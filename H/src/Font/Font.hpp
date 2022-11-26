#ifndef _FONT_HPP_
#define _FONT_HPP_

#include <wx/font.h>

namespace Fonts
{
	wxFont GetBoldFont(int pt)
	{
		return wxFont(pt, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	}

	wxFont GetExtraBoldFont(int pt)
	{
		return wxFont(pt, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD, false);
	}
}

#endif