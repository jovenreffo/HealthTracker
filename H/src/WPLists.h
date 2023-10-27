#ifndef _WORKOUTLIST_H_
#define _WORKOUTLIST_H_

#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/imaglist.h>
#include <vector>
#include "EntryList.h"
#include "RoutineStruct/Routine.h"
#include "RoutineView.h"

#define WPLIST_STYLE ( wxLC_REPORT | wxLC_SINGLE_SEL )

class WorkoutList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pMenu;

	wxImageList* m_pImageList;
	wxBitmap m_workoutBmp;

	std::vector<EntryContent> m_content;
	wxString m_currentItemName;
	long m_selectionIndex;

public:
	WorkoutList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = WPLIST_STYLE);
	~WorkoutList();

	// config
	void LoadFromConfig();
	void SaveToConfig();

	// setup
	void Init();
	void SetupImageList();
	void SetupColumn();
	void SetupMenu();

	void AddItem(const wxString& name, const wxString& content);
	void ResetList();

	void OpenWorkout();
	void OpenWorkout(const wxString& name);

	const std::vector<EntryContent>& GetContent() const { return m_content; }

	// events
	void OnRightClick(wxListEvent& event);
	void OnDoubleClick(wxListEvent& event);
	void OnItemSelected(wxListEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnDelete(wxCommandEvent& event);
};

class RoutineList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pMenu;

	std::vector<EntryContent> m_content;

	std::vector<Routine> m_routineInfo;

	RoutineView* m_pRoutineView;

	wxImageList* m_pImageList;
	wxBitmap m_routineBmp;

	wxString m_currentItemName;
	long m_selectionIndex;
	long m_insertionIndex{ 0 };

public:
	RoutineList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = WPLIST_STYLE);

	// Setup
	void Init();
	void SetupImageList();
	void SetupColumn();
	void SetupMenu();

	void SetContent(const std::vector<EntryContent>& content) { m_content = content; }
	void AddItem(const wxString& name, const Routine& routine);
	void ResetList();
	void OpenRoutine();

	// Events
	void OnRightClick(wxListEvent& event);
	void OnDoubleClick(wxListEvent& event);
	void OnItemSelected(wxListEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnDelete(wxCommandEvent& event);
};

#endif