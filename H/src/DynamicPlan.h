#ifndef DYNAMICPLAN_H
#define DYNAMICPLAN_H

#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/scrolwin.h>
#include "aui_includes/aui_includes.h"

#define LEP_SIZE (wxSize(125, 250))

enum class CEP
{
	ID_REPS_SPINCTRL,
	ID_ADD_REPS,
	ID_REP_COUNTER
};

class CounterList;

class CustomExercisePanel : public wxPanel
{
private:
	wxString m_exerciseName;

	// Sizers
	wxFlexGridSizer* m_pControlSizer;
	wxStaticBoxSizer* m_pTopSizer;
	wxStaticBox* m_pTopParent;

	// Controls
	wxSpinCtrl* m_pSpinCtrl;
	wxBitmapButton* m_pAddButton;
	CounterList* m_pCounterList;

	// Validator
	int m_repCount;

public:
	CustomExercisePanel(const wxString& exerciseName,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = LEP_SIZE,
		long style = 0L);
	~CustomExercisePanel();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnAddReps(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
};

class DynamicPlan : public wxScrolled<wxPanel>
{
private:
	wxAuiManager m_auiMgr;
	CustomExercisePanel* m_pCustomExercisePanel;

public:
	DynamicPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxVSCROLL | wxALWAYS_SHOW_SB);

	// Setup
	void Init();

	// Events

};

#endif