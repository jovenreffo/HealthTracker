#ifndef _ENTRYDIALOG_H_
#define _ENTRYDIALOG_H_

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>

#define ENTRY_DIALOG_STYLE (wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX)
#define ENTRY_DIALOG_SIZE (wxSize(300, 250))

class EntryDialog: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxButton* m_pOkButton;
	wxButton* m_pCancelButton;
	wxTextCtrl* m_pTextCtrl;
	wxStaticText* m_pNameText;

	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pNameSizer;
	wxBoxSizer* m_pButtonSizer;

public:
	EntryDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = ENTRY_DIALOG_SIZE,
		long style = ENTRY_DIALOG_STYLE);

	// Dialog setup
	void Init();
	void SetupSizes();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnOK(wxCommandEvent& event);
};

#endif