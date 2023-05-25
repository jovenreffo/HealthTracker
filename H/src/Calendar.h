#ifndef CALENDAR_H
#define CALENDAR_H

#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/generic/calctrlg.h>

class Calendar; // forward dec

enum class CID // Calendar ID
{
	ID_CAL_DCLICK
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