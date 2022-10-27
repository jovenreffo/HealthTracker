#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <wx/panel.h>

class Settings : public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

public:
	Settings(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Panel setup

	// Events

};

#endif