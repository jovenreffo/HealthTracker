#ifndef DYNAMICPLAN_H
#define DYNAMICPLAN_H

#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/scrolwin.h>
#include "aui_includes/aui_includes.h"

#define LEP_SIZE (wxSize(125, 250))

class CustomExercisePanel : public wxPanel
{
private:
	wxString m_exerciseName;

	// Sizers
	wxBoxSizer* m_pControlSizer;
	wxStaticBoxSizer* m_pTopSizer;
	wxStaticBox* m_pTopParent;

	// Controls
	wxSpinCtrl* m_pSpinCtrl;
	wxButton* m_pAddButton;
	wxListCtrl* m_pCounterList;

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
};

class DynamicPlan : public wxScrolled<wxPanel>
{
private:
	wxAuiManager m_auiMgr;

public:
	DynamicPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxVSCROLL | wxALWAYS_SHOW_SB);
};

#endif