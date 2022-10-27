#ifndef _JOURNAL_H_
#define _JOURNAL_H_

#include <wx/panel.h>

class Journal : public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

public:
	Journal(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif