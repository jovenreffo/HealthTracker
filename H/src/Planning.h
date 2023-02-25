#ifndef _CALENDAR_H_
#define _CALENDAR_H_

#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/splitter.h>
#include <wx/htmllbox.h>

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

class TodoPanel: public wxPanel
{
private:
	// Controls
	wxButton* m_pAddButton; wxBitmap m_addBmp;
	wxString m_objectiveStr;


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
// In this class deriving from wxHtmlListbox, there will be a spot for the objective name and description.
class TodoItem : public wxHtmlListBox
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

protected:
	// this function must be overridden
	virtual wxString OnGetItem(size_t n) const override;

public:
	wxDECLARE_NO_COPY_CLASS(TodoItem);
	wxDECLARE_DYNAMIC_CLASS(TodoItem);
};

#endif