#ifndef _FONT_HPP_
#define _FONT_HPP_

#include <wx/font.h>

namespace Fonts
{
	static __forceinline wxFont GetBoldFont(int pt)
	{
		return wxFont(pt, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	}

	static __forceinline wxFont GetExtraBoldFont(int pt)
	{
		return wxFont(pt, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD, false);
	}

	static __forceinline wxFont GetDefaultFont(int pt)
	{
		return wxFont(pt, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	}

	static __forceinline wxFont GetLightFont(int pt)
	{
		return wxFont(pt, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_THIN, false);
	}
}

#endif