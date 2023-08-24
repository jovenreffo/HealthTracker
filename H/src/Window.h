#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <wx/wx.h>
#include <wx/config.h>

#include "ListBook.h"
#include "Journal.h"
#include "Planning.h"
#include "Settings.h"
#include "ExercisePanel.h"
#include "ExerciseBook.h"
#include "AboutDialog/AboutDialog.h"
#include "TaskbarIcon.h"
#include "xpm/xpm_include.h"
#include "RoutineDialog.h"
#include "PrefsDlg.h"
#include "CaloriePanel.h"
#include "WorkoutWindow.h"
#include "MealPlanWindow.h"

class App: public wxApp
{
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;
};

#define WINDOW_SIZE (wxSize(895, 520))

enum
{
	ID_ENABLE_FULLSCREEN,
	ID_RESET_ENTRIES,
	ID_RESET_WORKOUTS,
	ID_RESET_ROUTINES,
	ID_ADD_WORKOUT,
	ID_ADD_ROUTINE,
	ID_ADD_NUTRITION_ITEM,
	ID_ADD_MEALPLAN,
	ID_PREFERENCES,
	ID_RESET_LAYOUT,
	ID_WINSIZE,
	ID_SUBMIT_REPORT
};

class Frame: public wxFrame
{
private:
	DECLARE_EVENT_TABLE()

private:
	// Menu bar
	wxMenuBar* m_pMenuBar;
	wxMenu* m_pFileMenu;
	wxMenu* m_pEditMenu;
	wxMenu* m_pViewMenu;
	wxMenu* m_pHelpMenu;
	wxMenu* m_pResetMenu; // submenu
	wxMenu* m_pAddMenu; // submenu
#ifdef _DEBUG
	wxMenu* m_pDebugMenu;
#endif
	Listbook* m_pListbook;
	AboutDialog* m_pAboutDialog;
	wxIcon m_heartIcon;
	TaskbarIcon* m_pTaskbarIcon;
	PrefsDlg* m_pPrefsDlg;

	WorkoutList* m_pWorkoutList;
	RoutineList* m_pRoutineList;
	EntryList* m_pEntryList;
	WorkoutWindow* m_pWorkoutDialog;
	RoutineDialog* m_pRoutineDialog;
	CaloriePanel* m_pCaloriePanel;
	MealPlanWindow* m_pMealPlanWindow;

	wxConfigBase* m_pConfig;
	
public:
	Frame();
	~Frame();

	bool ConfirmReset();

	// Getters
	WorkoutWindow* GetWorkoutDialog() const { return m_pWorkoutDialog; }

	// Window setup
	void Init();
	void InitConfig();
	void SetupTaskbarIcon();
	void SetupProgramIcon();
	void SetupMenuBar();
	void SetupSizes();
	void SetupListbook();
	void SetupLists();
	void SetupOther();

	// Events
	void OnExit(wxCommandEvent& event);
	void OnFullScreen(wxCommandEvent& event);
	void OnPreferences(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSubmitBugReport(wxCommandEvent& event);
	// reset events
	void OnResetAll(wxCommandEvent& event);
	void OnResetEntries(wxCommandEvent& event);
	void OnResetWorkouts(wxCommandEvent& event);
	void OnResetRoutines(wxCommandEvent& event);
	void OnResetWindowLayout(wxCommandEvent& event);
	// add events
	void OnAddWorkout(wxCommandEvent& event);
	void OnAddRoutine(wxCommandEvent& event);
	void OnAddNutritonItem(wxCommandEvent& event);
	// debug events
	void OnGetWindowSize(wxCommandEvent& event);
};

#endif