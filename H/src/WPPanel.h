#ifndef _WPPANEL_H_
#define _WPPANEL_H_

#include <wx/panel.h>
#include <wx/button.h>
#include <wx/splitter.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/sizer.h>
#include <wx/notebook.h>

#include "ExerciseBook/WorkoutWindow.h"
#include "ExerciseBook/WPLists/WPLists.h"


enum class WP
{
	ID_NEW_WORKOUT,
	ID_NEW_ROUTINE,
	ID_WORKOUT_WINDOW
};

// WP = workout plan
class WPPanel: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxNotebook* m_pWPNotebook; // 2 tabs: 1 will be for planned workouts, other for `plan-as-you-go`
	wxImageList* m_pImageList;
	wxBitmap m_checkBmp;
	wxBitmap m_randomBmp;

	WorkoutList* m_pWorkoutList;
	RoutineList* m_pRoutineList;
	wxTextCtrl* m_pTextInput;

	wxButton* m_pAddWorkoutButton;
	wxButton* m_pAddRoutineButton;

	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pBoxSizer;
	wxBoxSizer* m_pWorkoutSizer;
	wxBoxSizer* m_pRoutineSizer;

	wxSplitterWindow* m_pSplitter;
	wxPanel* m_pWorkoutPanel;
	wxPanel* m_pRoutinePanel;

	WorkoutWindow* m_pWorkoutWindow;

	wxPanel* temp;

public:
	WPPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Setup
	void Init();
	void SetupControls();
	void SetupPanels();
	void SetupSplitter();
	void ArrangeElements();
	void SetupNotebook();

	// Events
	void OnAddWorkout(wxCommandEvent& event);
};

#endif