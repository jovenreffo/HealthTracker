#ifndef _WPPANEL_H_
#define _WPPANEL_H_

#include <wx/panel.h>

// WP = workout plan
class WPPanel: public wxPanel
{
public:
	WPPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif