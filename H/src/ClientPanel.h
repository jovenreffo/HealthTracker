#ifndef CLIENTPANEL_H
#define CLIENTPANEL_H

#include <wx/wx.h>
#include <wx/font.h>
#include <wx/panel.h>
#include <wx/listctrl.h>

class ClientList : public wxListView
{
public:
	ClientList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_EDIT_LABELS);
};

class ClientPanel : public wxPanel
{
private:
	wxButton* m_pAddClientBtn;
	ClientList* m_pClientList;

public:
	ClientPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ClientPanel();

	// Panel setup
	void InitClientPanel();
	void SetupMemberControls();
	void SetupSizers();

	// Events
};

#endif