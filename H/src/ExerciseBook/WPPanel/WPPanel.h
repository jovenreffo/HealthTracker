#ifndef _WPPANEL_H_
#define _WPPANEL_H_

#include <wx/panel.h>
#include <wx/button.h>
#include <wx/splitter.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>

enum class WP
{
	ID_NEW_WORKOUT,
	ID_NEW_ROUTINE
};

// WP = workout plan
class WPPanel: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxListCtrl* m_pWorkoutList;
	wxListCtrl* m_pRoutineList;
	wxTextCtrl* m_pTextInput;

	wxButton* m_pHelpButton;
	wxButton* m_pAddWorkoutButton;
	wxButton* m_pAddRoutineButton;

	wxBoxSizer* m_pBoxSizer;
	wxBoxSizer* m_pWorkoutSizer;
	wxBoxSizer* m_pRoutineSizer;

	wxSplitterWindow* m_pSplitter;
	wxPanel* m_pWorkoutPanel;
	wxPanel* m_pRoutinePanel;

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

	// Events
	void OnHelp(wxCommandEvent& event);
	void OnAddWorkout(wxCommandEvent& event);
};

#endif