#include <wx/statline.h>
#include "WPPanel.h"

BEGIN_EVENT_TABLE(WPPanel, wxPanel)
	EVT_BUTTON(wxID_HELP, WPPanel::OnHelp)
END_EVENT_TABLE()

WPPanel::WPPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void WPPanel::Init()
{
	this->SetupControls();
	this->SetupSplitter();
	this->SetupPanels();
}

void WPPanel::SetupControls()
{
	m_pWorkoutList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pRoutineList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	
	m_pHelpButton = new wxButton(this, wxID_HELP, _T("Help"), wxDefaultPosition, wxDefaultSize);
	m_pAddWorkoutButton = new wxButton(this, wxID_ADD, _T("Add Workout"), wxDefaultPosition, wxDefaultSize);
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
	m_pSplitter = new wxSplitterWindow(this, wxID_ANY);
	m_pSplitter->SetSashGravity(0.5);
	m_pSplitter->SetMinimumPaneSize(100);
}

// Events
void WPPanel::OnHelp(wxCommandEvent& event)
{

}

void WPPanel::OnAddWorkout(wxCommandEvent& event)
{

}