#include <wx/statline.h>
#include "WPPanel.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(WPPanel, wxPanel)
	EVT_BUTTON(static_cast<int>(WP::ID_NEW_WORKOUT), WPPanel::OnAddWorkout)
END_EVENT_TABLE()

WPPanel::WPPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void WPPanel::Init()
{
	this->SetupNotebook();
	this->SetupSplitter();
	this->SetupPanels();
	this->SetupControls();
	this->ArrangeElements();
}

void WPPanel::SetupControls()
{
	m_pWorkoutList = new WorkoutList(m_pWorkoutPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pRoutineList = new RoutineList(m_pRoutinePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	m_pAddWorkoutButton = new wxButton(m_pWorkoutPanel, (int)WP::ID_NEW_WORKOUT, _T("Add Workout"), wxDefaultPosition, wxDefaultSize);
	m_pAddRoutineButton = new wxButton(m_pRoutinePanel, (int)WP::ID_NEW_ROUTINE, _T("Add Routine"), wxDefaultPosition, wxDefaultSize);
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

	// top level sizer for the notebook which contains all the items
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopSizer->Add(m_pWPNotebook, 1, wxEXPAND | wxALL, 5);
	m_pTopSizer->Add(m_pBoxSizer);

	m_pWPNotebook->AddPage(m_pSplitter, _T("Planned"), true, 0);
}

void WPPanel::SetupSplitter()
{
	m_pSplitter = new wxSplitterWindow(m_pWPNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	m_pSplitter->SetSashGravity(0.5);
	m_pSplitter->SetMinimumPaneSize(100);
}

void WPPanel::ArrangeElements()
{
	// Workout sizer
	m_pWorkoutSizer->Add(m_pAddWorkoutButton, 0, wxALIGN_LEFT | wxALL, 5);
	m_pWorkoutSizer->Add(new wxStaticLine(m_pWorkoutPanel, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	m_pWorkoutSizer->Add(m_pWorkoutList, 1, wxEXPAND | wxALL, 5);

	// Routine sizer
	m_pRoutineSizer->Add(m_pAddRoutineButton, 0, wxALIGN_LEFT | wxALL, 5);
	m_pRoutineSizer->Add(new wxStaticLine(m_pRoutinePanel, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	m_pRoutineSizer->Add(m_pRoutineList, 1, wxEXPAND | wxALL, 5);
}

void WPPanel::SetupNotebook()
{
	m_pWPNotebook = new wxNotebook(this, wxID_ANY);

	// icons
	m_checkBmp = wxBitmap(path_data::dataDir + _T("\\Images\\check.png"), wxBITMAP_TYPE_PNG);

	m_pImageList = new wxImageList(26, 26);
	m_pImageList->Add(m_checkBmp);
	m_pWPNotebook->AssignImageList(m_pImageList);
}

// Events

void WPPanel::OnAddWorkout(wxCommandEvent& event)
{
	m_pWorkoutWindow = new WorkoutWindow(this, static_cast<int>(WP::ID_WORKOUT_WINDOW), m_pWorkoutList);
	m_pWorkoutWindow->Show(true);
}
