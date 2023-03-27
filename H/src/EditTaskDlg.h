#ifndef EDITTASKDLG_H
#define EDITTASKDLG_H

#include <wx/wx.h>

#define ETD_SIZE (wxSize(315, 235))
#define ETD_SIZE_MAX (wxSize(415, 300))

class EditTaskDlg : public wxDialog
{
private:
	wxString m_taskName;
	wxString m_taskDesc;
	int m_priorityLevel;

	wxTextCtrl* m_pTaskName;
	wxTextCtrl* m_pTaskDesc; // wxTE_MULTILINE

	wxChoice* m_pPriorityLevel;
	wxArrayString m_priorityLevels;

	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pControlSizer;

public:
	EditTaskDlg() = default;
	EditTaskDlg(int priorityLevel,
		const wxString& taskName,
		const wxString& taskDesc,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Edit Task"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~EditTaskDlg();

	// Getters
	const wxString& GetTaskName() const { return m_taskName; }
	const wxString& GetTaskDesc() const { return m_taskDesc; }
	const int GetPriorityLevel()  const { return m_priorityLevel; }

	// Dialog setup
	void Init();
	void SetupPriorityLevels();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	void HandleExit();

	// Events
	void OnEnter(wxCommandEvent& e);
	void OnOK(wxCommandEvent& e);
	void OnCancel(wxCommandEvent& e);
	void OnMaxLengthName(wxCommandEvent& e);
	void OnMaxLengthDesc(wxCommandEvent& e);
};

#endif