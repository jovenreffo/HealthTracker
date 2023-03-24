#ifndef EDITTASKDLG_H
#define EDITTASKDLG_H

#include <wx/wx.h>

#define ETD_SIZE (wxSize(325, 275))

class EditTaskDlg : public wxDialog
{
private:
	wxString m_taskName;
	wxString m_taskDesc;

	wxTextCtrl* m_pTaskName;
	wxTextCtrl* m_pTaskDesc; // wxTE_MULTILINE

public:
	EditTaskDlg() = default;
	EditTaskDlg(const wxString& taskName,
		const wxString& taskDesc,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Edit Task"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~EditTaskDlg();

	// Dialog setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Eventgs
};

#endif