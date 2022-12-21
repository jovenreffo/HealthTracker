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

#include "WorkoutWindow.h"
#include "WPLists.h"
#include "DynamicPlan.h"
#include "RoutineDialog.h"
#include "WorkoutDialog.h"

enum class WP
{
	ID_NEW_WORKOUT,
	ID_NEW_ROUTINE,
	ID_WORKOUT_DIALOG
};

// WP = workout plan
class WPNotebook: public wxNotebook
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxNotebook* m_pWPNotebook; // 2 tabs: 1 will be for planned workouts, other for `plan-as-you-go`
	wxImageList* m_pImageList;
	wxBitmap m_checkBmp;
	wxBitmap m_randomBmp;
	wxBitmap m_addBmp;

	WorkoutList* m_pWorkoutList;
	RoutineList* m_pRoutineList;
	WorkoutDialog* m_pWorkoutDialog;
	RoutineDialog* m_pRoutineDialog;

	// Controls for planned workouts tab
	wxButton* m_pAddWorkoutButton;
	wxButton* m_pAddRoutineButton;

	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pBoxSizer;
	wxBoxSizer* m_pWorkoutSizer;
	wxBoxSizer* m_pRoutineSizer;

	wxSplitterWindow* m_pSplitter;
	wxPanel* m_pWorkoutPanel;
	wxPanel* m_pRoutinePanel;
	
	DynamicPlan* m_pDynamicPlan;

public:
	WPNotebook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	~WPNotebook();

	WorkoutList* GetWorkoutList() const { return m_pWorkoutList; }
	RoutineList* GetRoutineList() const { return m_pRoutineList; }

	// Setup
	void Init();
	void SetupControls();
	void SetupPanels();
	void SetupSplitter();
	void ArrangeElements();
	void SetupNotebook();

	void CreateNewRoutine();
	void CreateNewWorkout();

	// Events
	void OnAddWorkout(wxCommandEvent& WXUNUSED(event));
	void OnAddRoutine(wxCommandEvent& WXUNUSED(event));
};

#endif