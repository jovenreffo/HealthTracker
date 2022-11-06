#ifndef _WORKOUTLIST_H_
#define _WORKOUTLIST_H_

#include <wx/listctrl.h>

#define LIST_STYLE ( wxLC_REPORT | wxLC_SINGLE_SEL )

class WorkoutList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

public:
	WorkoutList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = LIST_STYLE);
};

class RoutineList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

public:
	RoutineList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = LIST_STYLE);
};

#endif