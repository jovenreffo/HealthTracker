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

#define CEP_SIZE (wxSize(125, 250))

#define AED_SIZE (wxSize(280, 160))
#define AED_SIZE_MAX (wxSize(340, 180))

enum class CEP
{
	ID_REPS_SPINCTRL,
	ID_ADD_REPS,
	ID_REP_COUNTER
};

class CounterList;
class ExerciseNotebook; // Inherits from wxAuiNotebook, dockable & movable tabs will be nice for the user

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
		const wxSize& size = CEP_SIZE,
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

class AddExerciseDialog : public wxDialog
{
private:
	// Controls
	wxTextCtrl* m_pExerciseNameTxt;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxFlexGridSizer* m_pHorizontalSizer;

	// Validator
	wxString m_exerciseName;

public:
	AddExerciseDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Add Exercise"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);

	// Setup
	void Init();
	void SetupSizing();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};

class DynamicPlan : public wxScrolled<wxPanel>
{
private:
	// Controls
	wxButton* m_pAddExercise; wxBitmap m_addBmp;
	wxButton* m_pOpenSpreadSheet; wxBitmap m_spreadsheetBmp;
	AddExerciseDialog* m_pAddExerciseDialog;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pTopButtonSizer;

	// AUI
	ExerciseNotebook* m_pExerciseNotebook;
	wxAuiManager m_auiMgr;
	wxString m_perspective;
	wxString m_defPerspective;

public:
	DynamicPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxVSCROLL | wxALWAYS_SHOW_SB);
	~DynamicPlan();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupAUI();

	// Events
	void OnAddExercise(wxCommandEvent& event);
	void OnOpenSpreadsheet(wxCommandEvent& event);
};

class ExerciseNotebook : public wxAuiNotebook
{
private:
	

public:
	ExerciseNotebook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxAUI_NB_DEFAULT_STYLE);
};

#endif