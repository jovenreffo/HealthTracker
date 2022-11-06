#include "WPLists.h"

// event table for WorkoutList
BEGIN_EVENT_TABLE(WorkoutList, wxListView)

END_EVENT_TABLE()

// event table for RoutineList
BEGIN_EVENT_TABLE(RoutineList, wxListView)

END_EVENT_TABLE()

WorkoutList::WorkoutList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView{ parent, id, pos, size, style }
{
}


RoutineList::RoutineList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView{ parent, id, pos, size, style }
{
}

