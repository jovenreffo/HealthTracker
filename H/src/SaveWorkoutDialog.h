#ifndef _SAVEWORKOUTDIALOG_H_
#define _SAVEWORKOUTDIALOG_H_

#include <wx/dialog.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>

#define SWDIALOG_SIZE	  (wxSize(250, 150))
#define SWDIALOG_SIZE_MAX (wxSize(275, 175))

class SaveWorkoutDialog: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxTextCtrl* m_pTextCtrl;
	wxStaticText* m_pNameText;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxString m_textValue;

public:
	SaveWorkoutDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = SWDIALOG_SIZE,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);

	// Dialog setup
	void Init();
	void SetupControls();

	const wxString GetWorkoutName() const { return m_textValue; }

	// Events
	void OnOK(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
};

#endif