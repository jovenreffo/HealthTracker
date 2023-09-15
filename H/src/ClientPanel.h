#ifndef CLIENTPANEL_H
#define CLIENTPANEL_H

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/font.h>
#include <wx/panel.h>
#include <wx/listctrl.h>

class ClientList : public wxListView
{
private:
	wxFont m_font; // The font used for items in the list will be bigger, and slightly bolded.

	// Controls
	wxMenu* m_pMenu;
	wxImageList* m_pImageList;

	// Bitmaps, icons, images
	wxBitmap m_clientIconBmp;

public:
	ClientList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_EDIT_LABELS);

	// Setup
	void SetupList();
	void SetupColumn();
	void SetupImageList();
	void SetupMenu();
	void SetListFont();
	
	// Actions & events
	void AddItem(const wxString& name);
};

class ClientPanel : public wxPanel
{
private:
	// Controls
	wxButton* m_pAddClientBtn;
	ClientList* m_pClientList;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pTopButtonSizer;

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