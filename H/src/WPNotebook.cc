#include <wx/statline.h>
#include "WPNotebook.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(WPNotebook, wxNotebook)
	EVT_BUTTON(static_cast<int>(WP::ID_NEW_WORKOUT), WPNotebook::OnAddWorkout)
	EVT_BUTTON(static_cast<int>(WP::ID_NEW_ROUTINE), WPNotebook::OnAddRoutine)
END_EVENT_TABLE()

WPNotebook::WPNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxNotebook(parent, id, pos, size, style)
{
	this->Init();

}

WPNotebook::~WPNotebook()
{
	this->DestroyChildren();
}

void WPNotebook::Init()
{
	this->SetupNotebook();
	this->SetupSplitter();
	this->SetupPanels();
	this->SetupControls();
	this->ArrangeElements();
}

void WPNotebook::SetupControls()
{
	m_pWorkoutList = new WorkoutList(m_pWorkoutPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pRoutineList = new RoutineList(m_pRoutinePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	m_pAddWorkoutButton = new wxButton(m_pWorkoutPanel, static_cast<int>(WP::ID_NEW_WORKOUT), _T("Add Workout"), wxDefaultPosition, wxDefaultSize);
	m_pAddRoutineButton = new wxButton(m_pRoutinePanel, static_cast<int>(WP::ID_NEW_ROUTINE), _T("Add Routine"), wxDefaultPosition, wxDefaultSize);
}

void WPNotebook::SetupPanels()
{
	m_pWorkoutPanel = new wxPanel(m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pRoutinePanel = new wxPanel(m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pDynamicPlan = new DynamicPlan(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	m_pWorkoutSizer = new wxBoxSizer(wxVERTICAL);
	m_pRoutineSizer = new wxBoxSizer(wxVERTICAL);
	m_pWorkoutPanel->SetSizerAndFit(m_pWorkoutSizer);
	m_pRoutinePanel->SetSizerAndFit(m_pRoutineSizer);

	m_pSplitter->SplitVertically(m_pWorkoutPanel, m_pRoutinePanel);

	this->AddPage(m_pSplitter, _T("Planned Workouts"), true, 0);
	this->AddPage(m_pDynamicPlan, _T("Track-On-The-Go"), false, 1);
}

void WPNotebook::SetupSplitter()
{
	m_pSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH | wxSP_LIVE_UPDATE | wxSP_NOBORDER);
	m_pSplitter->SetSashGravity(0.5);
	m_pSplitter->SetMinimumPaneSize(100);
}

void WPNotebook::ArrangeElements()
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

void WPNotebook::SetupNotebook()
{
	// icons
	m_checkBmp = wxBitmap(path_data::dataDir + _T("\\Images\\check.png"), wxBITMAP_TYPE_PNG);
	m_randomBmp = wxBitmap(path_data::dataDir + _T("\\Images\\random.png"), wxBITMAP_TYPE_PNG);
	m_checkBmp.ResetAlpha();
	m_randomBmp.ResetAlpha();

	m_pImageList = new wxImageList(26, 26);
	m_pImageList->Add(m_checkBmp);
	m_pImageList->Add(m_randomBmp);
	this->AssignImageList(m_pImageList);
}

void WPNotebook::CreateNewRoutine()
{
	m_pRoutineDialog = new RoutineDialog(m_pWorkoutList->GetContent(), m_pRoutineList, this, static_cast<int>(WP::ID_NEW_ROUTINE), _T("New Routine"));
	m_pRoutineList->SetContent(m_pWorkoutList->GetContent());
	m_pRoutineDialog->Show(true);
}

void WPNotebook::CreateNewWorkout()
{
	m_pWorkoutDialog = new WorkoutDialog(m_pWorkoutList, this, static_cast<int>(WP::ID_WORKOUT_DIALOG), _T("Create New Workout"), wxDefaultPosition, wxDefaultSize);
	m_pWorkoutDialog->Show(true);
}

// Events

void WPNotebook::OnAddWorkout(wxCommandEvent& WXUNUSED(event))
{
	this->CreateNewWorkout();
}

void WPNotebook::OnAddRoutine(wxCommandEvent& WXUNUSED(event))
{
	this->CreateNewRoutine();
}
