#ifndef CALENDAR_H
#define CALENDAR_H

#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/generic/calctrlg.h>
#include <wx/textctrl.h>

class Calendar; // forward dec

enum class CID // Calendar ID
{
	ID_CAL_DCLICK
};

class CalendarPlanDlg : public wxDialog
{
private:


public:
	CalendarPlanDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Select date:"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~CalendarPlanDlg();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
};

class CalendarPanel : public wxPanel
{
private:
	Calendar* m_pCalendar;

	wxBoxSizer* m_pTopSizer;

public:
	CalendarPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~CalendarPanel();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
};

class Calendar : public wxGenericCalendarCtrl
{
public:
	Calendar(wxWindow* parent,
		wxWindowID id,
		const wxDateTime& dt = wxDefaultDateTime,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAL_SHOW_HOLIDAYS);
	~Calendar();

	// Calendar events
	void OnSelectDay(wxCalendarEvent& event);
	void OnDoubleClickDay(wxCalendarEvent& event);
};

#endif