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

#define ADDTODOITEMDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )
#define ADDTODOITEMDLG_SIZE ( wxSize(365, 345) )
#define ADDTODOITEMDLG_MAX_SiZE	( wxSize(550, 375) )

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

class AddTodoItemDlg : public wxDialog
{
public:
	AddTodoItemDlg() = default;
	AddTodoItemDlg(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& title = _T("Add Objective"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = ADDTODOITEMDLG_SIZE,
		long style = ADDTODOITEMDLG_STYLE);

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

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pObjectiveSizer;

public:
	TodoPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Other
	const wxString& GetObjective() const { return m_objectiveStr; }

	// Panel setup
	void Init();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnTextEnter(wxCommandEvent& event);
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