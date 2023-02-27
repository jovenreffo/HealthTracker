#ifndef _CALENDAR_H_
#define _CALENDAR_H_

#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/splitter.h>
#include <wx/htmllbox.h>

#define ADDTASKDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )
#define ADDTASKDLG_SIZE ( wxSize(365, 345) )
#define ADDTASKDLG_MAX_SIZE	( wxSize(550, 375) )

enum class TD
{
	ID_ADD_TODO
};

class CalendarPanel;
class TodoPanel;

class Calendar: public wxNotebook
{
private:

private:
	// Visuals
	wxImageList* m_pImageList;
	wxBitmap m_calendarBmp;
	wxBitmap m_todoBmp;

	// Content panels
	CalendarPanel* m_pCalendarPanel;
	TodoPanel* m_pTodoPanel;

public:
	Calendar(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	
	// Book setup
	void Init();
	void SetupImageList();
	void SetupPages();
};

class CalendarPanel: public wxPanel
{
private:

public:
	CalendarPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

class AddTaskDlg : public wxDialog
{
private:
	// Controls
	wxButton* m_pOk;
	wxButton* m_pCancel;
	wxTextCtrl* m_pTaskNameTxt;
	wxTextCtrl* m_pTaskDescTxt;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pTextSizer;

public:
	AddTaskDlg() = default;
	AddTaskDlg(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& title = _T("Add Task"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = ADDTASKDLG_SIZE,
		long style = ADDTASKDLG_STYLE);
	~AddTaskDlg();

	// Dialog setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();
};

class TodoPanel: public wxScrolled<wxPanel>
{
private:
	// Controls
	wxButton* m_pAddButton; wxBitmap m_addBmp;
	wxString m_objectiveStr;
	AddTaskDlg* m_pAddTaskDlg;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pObjectiveSizer;

public:
	TodoPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~TodoPanel();

	// Other
	const wxString& GetObjective() const { return m_objectiveStr; }

	// Panel setup
	void Init();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnTextEnter(wxCommandEvent& event);
	void OnAddTask(wxCommandEvent& event);
};

// For the to-do list items, customization will be needed.
// In this class deriving from wxPanel, there will be a spot for the objective name and description, and a checkbox for completing the task
class TodoItem : public wxPanel
{
public:
	TodoItem() = default;
	TodoItem(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L,
		const wxString& name = wxHtmlListBoxNameStr);

	void Init();

public:
	wxDECLARE_NO_COPY_CLASS(TodoItem);
	wxDECLARE_DYNAMIC_CLASS(TodoItem);
};

#endif