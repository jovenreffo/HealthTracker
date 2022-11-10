#ifndef _WORKOUTLIST_H_
#define _WORKOUTLIST_H_

#include <wx/listctrl.h>
#include <wx/menu.h>

#define WPLIST_STYLE ( wxLC_REPORT | wxLC_SINGLE_SEL )

class WorkoutList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pMenu;

public:
	WorkoutList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = WPLIST_STYLE);

	// setup
	void SetupColumn();
	void SetupMenu();

	// events
	void OnRightClick(wxListEvent& event);
	void OnDoubleClick(wxListEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnDelete(wxCommandEvent& event);
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
		long style = WPLIST_STYLE);

	void SetupColumn();
};

#endif