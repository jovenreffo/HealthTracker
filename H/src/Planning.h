#ifndef _CALENDAR_H_
#define _CALENDAR_H_

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include <wx/htmllbox.h>
#include <vector>

#define ADDTASKDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )
#define ADDTASKDLG_SIZE ( wxSize(315, 235) )
#define ADDTASKDLG_MAX_SIZE	( wxSize(415, 300) )

class CalendarPanel;
class TodoPanel;
class TodoItem;
class TaskList;
class PriorityLevel;

class Planning: public wxNotebook
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
	Planning(wxWindow* parent,
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

	// Control members for urgency selector
	wxChoice* m_pPriorityLevel;
	wxArrayString m_priorityLevels;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pTextSizer;

	// Validators
	wxString m_taskName;
	wxString m_taskDesc;

public:
	AddTaskDlg() = default;
	AddTaskDlg(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& title = _T("Add Task"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = ADDTASKDLG_SIZE,
		long style = ADDTASKDLG_STYLE);
	~AddTaskDlg();

	// Getters
	const wxString& GetTaskName() const { return m_taskName; }
	const wxString& GetTaskDesc() const { return m_taskDesc; }

	// Dialog setup
	void Init();
	void SetupPriorityLevels();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	void HandleExit();
	
	// Events
	void OnTextEnter(wxCommandEvent& e);
	void OnOK(wxCommandEvent& e);
	void OnCancel(wxCommandEvent& e);
	void OnMaxLengthName(wxCommandEvent& e);
	void OnMaxLengthDesc(wxCommandEvent& e);
};

class TodoPanel: public wxScrolled<wxPanel>
{
private:
	// Controls
	wxButton* m_pAddButton; wxBitmap m_addBmp;
	wxButton* m_pClearListButton; wxBitmap m_checkBmp;
	wxString m_objectiveStr;
	AddTaskDlg* m_pAddTaskDlg;
	TaskList* m_pTaskList;

	// Splitter
	wxSplitterWindow* m_pSplitter;
	wxPanel* m_pTaskPanel;
	wxPanel* m_pCompletedPanel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pTopButtonSizer;
	wxStaticBoxSizer* m_pListSizer;
	// Sizers for panels
	wxBoxSizer* m_pCompletedSizer;
	wxBoxSizer* m_pTaskSizer;

	// Vector for storing each of the user's items
	std::vector<TodoItem*> m_items;

public:
	TodoPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxVSCROLL | wxALWAYS_SHOW_SB);
	~TodoPanel();

	// Getters
	const wxString& GetObjective() const { return m_objectiveStr; }

	// Panel setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupPanels();
	void SetupSplitter();

	void AddTask(const wxString& name, const wxString& desc);

	// Events
	void OnAddTask(wxCommandEvent& e);
	void OnClearTaskList(wxCommandEvent& e);
};

// For the to-do list items, customization will be needed.
// In this class deriving from wxPanel, there will be a spot for the objective name and description, and a checkbox for completing the task
class TodoItem : public wxPanel
{
private:
	wxString m_taskName;
	wxString m_taskDesc;
	TaskList* m_pTaskList;

	PriorityLevel* m_pPriorityLevel;
	wxPaintDC m_dc;

	// Controls
	wxCheckBox* m_pMarkCompleted;
	wxMenu* m_pMenu;

	// Text objects to be arranged
	wxStaticText* m_pNameTitle;
	wxStaticText* m_pDescTitle;
	wxStaticText* m_pItemName;
	wxStaticText* m_pItemDesc;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxFlexGridSizer* m_pFlexSizer;

public:
	TodoItem(const wxString& taskName,
		const wxString& taskDesc,
		TaskList* pTaskList,
		wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L,
		const wxString& name = wxHtmlListBoxNameStr);
	~TodoItem();

	// getters
	const wxString& GetTaskName() const { return m_taskName; }
	const wxString& GetTaskDesc() const { return m_taskDesc; }

	// panel setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupPopupMenu();

	void HandleDelete();

	// events
	void OnMarkCompleted(wxCommandEvent& e);
	void OnRightClick(wxMouseEvent& e);
	void OnRemove(wxCommandEvent& e);
	void OnPaint(wxPaintEvent& e);
};

class TaskList : public wxListView
{
private:
	wxMenu* m_pMenu;

	wxImageList* m_pImageList;
	wxBitmap m_taskBmp;

	// List info
	wxString m_currentItemName;
	long m_selectionIndex;

public:
	TaskList() = default;
	TaskList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);
	~TaskList();

	// List setup
	void Init();
	void SetupImageList();
	void SetupColumn();
	void SetupMenu();

	void AddItem(const wxString& name);

	// Events
	void OnItemSelected(wxListEvent& e);
	void OnRightClickItem(wxListEvent& e);
	void OnRemoveItem(wxCommandEvent& e);
};

class PriorityLevel : public wxClientDC
{
public:
	PriorityLevel(wxWindow* parent);
};

#endif