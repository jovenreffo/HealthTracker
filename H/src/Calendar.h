#ifndef _CALENDAR_H_
#define _CALENDAR_H_

#include <wx/panel.h>

class Calendar: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

public:
	Calendar(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif