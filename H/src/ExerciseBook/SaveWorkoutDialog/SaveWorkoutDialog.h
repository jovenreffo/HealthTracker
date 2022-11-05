#ifndef _SAVEWORKOUTDIALOG_H_
#define _SAVEWORKOUTDIALOG_H_

#include <wx/dialog.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/button.h>

class SaveWorkoutDialog: public wxDialog
{
private:
	DECLARE_CLASS(SaveWorkoutDialog)
	DECLARE_EVENT_TABLE()

private:
	wxTextCtrl* m_pTextCtrl;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxString m_textValue;

public:
	SaveWorkoutDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);

	// Dialog setup
	void Init();
	void SetupControls();
};

#endif