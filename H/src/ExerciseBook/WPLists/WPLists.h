#ifndef _WORKOUTLIST_H_
#define _WORKOUTLIST_H_

#include <wx/listctrl.h>
#include <wx/menu.h>

#define WPLIST_STYLE ( wxLC_REPORT | wxLC_SINGLE_SEL )

// this struct will store a wxString array of <size> elements. Each workout will be stored in a string
template<int size>
struct ContentStore
{
	wxString m_content[size];

	wxString& operator[](int i)
	{
		return m_content[i];
	}

	int GetSize() const { return size; }
};

class WorkoutList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pMenu;
	ContentStore<100> m_contentStore;

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