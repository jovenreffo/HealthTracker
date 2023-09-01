#ifndef BUGREPORT_H
#define BUGREPORT_H

#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include <array>
#include "PrefsDlg.h"


class BugReport : public wxDialog
{
private:
	// Controls
	std::array<wxBitmapButton*, 2> m_pModifyBtn;
	wxTextCtrl* m_pNameTxt;
	wxTextCtrl* m_pEmailTxt;
	wxTextCtrl* m_pReportTxt;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	PrefsDlg* m_pPrefsDlg;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pControlSizer;

	// Values
	wxString m_name;
	wxString m_email;

public:
	BugReport(PrefsDlg* pPrefsDlg,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~BugReport();

	// Setup for dialog
	void Init();
	void LoadConfig();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events for buttons
	void OnModify(wxCommandEvent& event);
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

#endif