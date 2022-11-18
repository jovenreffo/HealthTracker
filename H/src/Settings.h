#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <wx/panel.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>

#include "WPNotebook.h"
#include "ExercisePanel.h"
#include "Journal.h"

// SE, Settings Enum
enum class SE
{
	ID_RESET_ALL,
	ID_RESET_ENTRIES,
	ID_RESET_WORKOUTS,
	ID_RESET_ROUTINES
};

class Settings: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxStaticBoxSizer* m_pTopSizer;
	wxStaticBoxSizer* m_pResetBox;
	wxStaticBox* m_pTopParent;
	
	wxButton* m_pResetAll;
	wxButton* m_pResetEntries;
	wxButton* m_pResetWorkouts;
	wxButton* m_pResetRoutines;

	// Vars that are passed to the ctor
	ExercisePanel* m_pExercisePanel;
	WPNotebook* m_WPNotebook;
	Journal* m_pJournal;

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
	void SetupControls();
	void SetupSizers();
	
	// Controls
	void AddAllControls();
	void AddResetGroup();

	// Events
	void OnResetAll(wxCommandEvent& WXUNUSED(event));
	void OnResetEntries(wxCommandEvent& WXUNUSED(event));
	void OnResetWorkouts(wxCommandEvent& WXUNUSED(event));
	void OnResetRoutines(wxCommandEvent& WXUNUSED(event));
};

#endif