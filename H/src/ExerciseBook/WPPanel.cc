#include <wx/statline.h>
#include "WPPanel.h"

BEGIN_EVENT_TABLE(WPPanel, wxPanel)
	EVT_BUTTON(wxID_HELP, WPPanel::OnHelp)
	EVT_BUTTON(static_cast<int>(WP::ID_NEW_WORKOUT), WPPanel::OnAddWorkout)
END_EVENT_TABLE()

WPPanel::WPPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void WPPanel::Init()
{
	this->SetupSplitter();
	this->SetupPanels();
	this->SetupControls();
	this->ArrangeElements();
}

void WPPanel::SetupControls()
{
	m_pWorkoutList = new wxListCtrl(m_pWorkoutPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	m_pRoutineList = new wxListCtrl(m_pRoutinePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);

	// initialize columns for the lists
	this->SetupLists();
	
	m_pHelpButton = new wxButton(this, wxID_HELP, _T("Help"), wxDefaultPosition, wxDefaultSize);
	m_pAddWorkoutButton = new wxButton(m_pWorkoutPanel, (int)WP::ID_NEW_WORKOUT, _T("Add Workout"), wxDefaultPosition, wxDefaultSize);
	m_pAddRoutineButton = new wxButton(m_pRoutinePanel, (int)WP::ID_NEW_ROUTINE, _T("Add Routine"), wxDefaultPosition, wxDefaultSize);
}

void WPPanel::SetupLists()
{
	wxListItem routineCol;
	wxListItem workoutCol;

	routineCol.SetText(_T("Routines"));
	workoutCol.SetText(_T("Workouts"));

	routineCol.SetImage(-1);
	workoutCol.SetImage(-1);

	m_pRoutineList->InsertColumn(0, routineCol);
	m_pWorkoutList->InsertColumn(0, workoutCol);

	m_pRoutineList->SetColumnWidth(0, 200);
	m_pWorkoutList->SetColumnWidth(0, 200);
}

void WPPanel::SetupPanels()
{
	m_pWorkoutPanel = new wxPanel(m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pRoutinePanel = new wxPanel(m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	m_pWorkoutSizer = new wxBoxSizer(wxVERTICAL);
	m_pRoutineSizer = new wxBoxSizer(wxVERTICAL);
	m_pWorkoutPanel->SetSizerAndFit(m_pWorkoutSizer);
	m_pRoutinePanel->SetSizerAndFit(m_pRoutineSizer);

	m_pSplitter->SplitVertically(m_pWorkoutPanel, m_pRoutinePanel);

	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	m_pBoxSizer->Add(m_pSplitter, 1, wxEXPAND | wxALL, 5);
	this->SetSizerAndFit(m_pBoxSizer);
}

void WPPanel::SetupSplitter()
{
	m_pSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	m_pSplitter->SetSashGravity(0.5);
	m_pSplitter->SetMinimumPaneSize(100);
}

void WPPanel::ArrangeElements()
{
	// Top-level sizer
	m_pBoxSizer->Add(m_pHelpButton, 0, wxALIGN_LEFT | wxALL, 5);

	// Workout sizer
	m_pWorkoutSizer->Add(m_pAddWorkoutButton, 0, wxALIGN_LEFT | wxALL, 5);
	m_pWorkoutSizer->Add(new wxStaticLine(m_pWorkoutPanel, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	m_pWorkoutSizer->Add(m_pWorkoutList, 1, wxEXPAND | wxALL, 5);

	// Routine sizer
	m_pRoutineSizer->Add(m_pAddRoutineButton, 0, wxALIGN_LEFT | wxALL, 5);
	m_pRoutineSizer->Add(new wxStaticLine(m_pRoutinePanel, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	m_pRoutineSizer->Add(m_pRoutineList, 1, wxEXPAND | wxALL, 5);
}

// Events
void WPPanel::OnHelp(wxCommandEvent& event)
{

}

void WPPanel::OnAddWorkout(wxCommandEvent& event)
{
	m_pWorkoutWindow = new WorkoutWindow(this, static_cast<int>(WP::ID_WORKOUT_WINDOW));
	m_pWorkoutWindow->Show(true);

}
