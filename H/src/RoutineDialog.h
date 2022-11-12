#ifndef _ROUTINEDIALOG_H_
#define _ROUTINEDIALOG_H_

#include <wx/dialog.h>

#define RDLG_SIZE ( wxSize(250, 400) )
#define RDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )

class RoutineDialog: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:

public:
	RoutineDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = RDLG_SIZE,
		long style = RDLG_STYLE);

	// Setup
	void Init();
	void SetupControls();
	void CreateControls();

	// Events
	void OnOK(wxCommandEvent& WXUNUSED(event));
	void OnClose(wxCloseEvent& WXUNUSED(event));
};

#endif