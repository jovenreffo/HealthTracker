#ifndef CALENDAR_H
#define CALENDAR_H

#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/generic/calctrlg.h>

class Calendar; // forward dec

class CalendarPanel : public wxPanel
{
private:
	Calendar* m_pCalendar;

public:
	CalendarPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
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
};

#endif