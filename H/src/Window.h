#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <wx/wx.h>
#include <wx/config.h>
#include "ListBook.h"
#include "Journal.h"
#include "Calendar.h"
#include "Settings.h"
#include "ExercisePanel.h"
#include "ExerciseBook.h"
#include "AboutDialog/AboutDialog.h"
#include "TaskbarIcon.h"
#include "xpm/xpm_include.h"
#include "RoutineDialog.h"
#include "PrefsDlg.h"
#include "CaloriePanel.h"
#include "WorkoutDialog.h"
#include "MealPlanWindow.h"

class App: public wxApp
{
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;
};

#define WINDOW_SIZE (wxSize(640, 480))

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
	ID_PREFERENCES
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

	Listbook* m_pListbook;
	AboutDialog* m_pAboutDialog;
	wxIcon m_heartIcon;
	TaskbarIcon* m_pTaskbarIcon;
	PrefsDlg* m_pPrefsDlg;

	WorkoutList* m_pWorkoutList;
	RoutineList* m_pRoutineList;
	EntryList* m_pEntryList;
	WorkoutDialog* m_pWorkoutDialog;
	RoutineDialog* m_pRoutineDialog;
	CaloriePanel* m_pCaloriePanel;
	MealPlanWindow* m_pMealPlanWindow;

	wxConfigBase* m_pConfig;
	
public:
	Frame();
	~Frame();

	bool ConfirmReset();

	// Getters
	WorkoutDialog* GetWorkoutDialog() const { return m_pWorkoutDialog; }

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
	void OnAbout(wxCommandEvent& event);
	void OnPreferences(wxCommandEvent& event);
	// reset events
	void OnResetAll(wxCommandEvent& WXUNUSED(event));
	void OnResetEntries(wxCommandEvent& WXUNUSED(event));
	void OnResetWorkouts(wxCommandEvent& WXUNUSED(event));
	void OnResetRoutines(wxCommandEvent& WXUNUSED(event));
	// add events
	void OnAddWorkout(wxCommandEvent& WXUNUSED(event));
	void OnAddRoutine(wxCommandEvent& WXUNUSED(event));
	void OnAddNutritonItem(wxCommandEvent& WXUNUSED(event));
	void OnAddMealPlan(wxCommandEvent& WXUNUSED(event));
};

#endif