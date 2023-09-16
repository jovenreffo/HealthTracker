#ifndef CLIENTPANEL_H
#define CLIENTPANEL_H

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/font.h>
#include <wx/panel.h>
#include <wx/listctrl.h>

class NewClientDlg : public wxDialog
{
private:
	// Controls
	wxTextCtrl* m_pClientNameTxt;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers


	// Validators
	wxString m_clientName;

public:
	NewClientDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Add New Client"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~NewClientDlg();

	// Setup
	void SetupNewClientDlg();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

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
	NewClientDlg* m_pNewClientDlg;

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
	void OnAddClient(wxCommandEvent& event);
};

#endif