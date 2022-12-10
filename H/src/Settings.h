#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <wx/panel.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/listbook.h>

#include "WPNotebook.h"
#include "ExercisePanel.h"
#include "Journal.h"

// SE, Settings Enum
enum class SE
{
	ID_RESET_ALL,
	ID_RESET_ENTRIES,
	ID_RESET_WORKOUTS,
	ID_RESET_ROUTINES,
	ID_ADD_WORKOUT,
	ID_ADD_ROUTINE,
	ID_ADD_NUTR_ITEM
};

class Settings: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxStaticBoxSizer* m_pTopSizer;
	wxStaticBoxSizer* m_pResetBox;
	wxStaticBoxSizer* m_pAddItemBox;
	wxStaticBox* m_pTopParent;
	
	wxButton* m_pResetAll;
	wxButton* m_pResetEntries;
	wxButton* m_pResetWorkouts;
	wxButton* m_pResetRoutines;

	wxButton* m_pAddWorkout;
	wxButton* m_pAddRoutine;
	wxButton* m_pAddNutrItem;

	// Window pointers
	ExercisePanel* m_pExercisePanel;
	ExerciseBook* m_pExerciseBook;
	NutritionPanel* m_pNutrPanel;
	NutritionBook* m_pNutrBook;
	CaloriePanel* m_pCaloriePanel;
	WPNotebook* m_WPNotebook;
	Journal* m_pJournal;
	wxListbook* m_pListbook;

public:
	Settings(ExercisePanel* pExercisePanel,
		Journal* pJournal,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Panel/control setup
	void Init();
	void InitWindowPointers();
	void SetupControls();
	void SetupSizers();
	
	// Controls
	void AddAllControls();
	void AddResetGroup();
	void AddItemsGroup();

	// Events
	void OnResetAll(wxCommandEvent& WXUNUSED(event));
	void OnResetEntries(wxCommandEvent& WXUNUSED(event));
	void OnResetWorkouts(wxCommandEvent& WXUNUSED(event));
	void OnResetRoutines(wxCommandEvent& WXUNUSED(event));
	void OnAddWorkout(wxCommandEvent& WXUNUSED(event));
	void OnAddRoutine(wxCommandEvent& WXUNUSED(event));
	void OnAddNutritionItem(wxCommandEvent& WXUNUSED(event));

	bool ConfirmReset();
};

#endif