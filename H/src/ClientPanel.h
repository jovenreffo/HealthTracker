#ifndef CLIENTPANEL_H
#define CLIENTPANEL_H

#include <wx/panel.h>
#include <wx/wx.h>

class ClientPanel : public wxPanel
{
public:
	ClientPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif