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
	this->SetupSizers();
}

void WPPanel::SetupControls()
{
	m_pWorkoutList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//m_pRoutineList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	m_pHelpButton = new wxButton(this, wxID_HELP, _T("Help"), wxDefaultPosition, wxDefaultSize);
	m_pAddWorkoutButton = new wxButton(this, wxID_ADD, _T("Add Workout"), wxDefaultPosition, wxDefaultSize);
}

void WPPanel::SetupSizers()
{
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pBoxSizer);

	m_pBoxSizer->Add(m_pHelpButton, 0, wxALIGN_LEFT | wxALL, 5);
	m_pBoxSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	m_pBoxSizer->Add(m_pWorkoutList, 1, wxEXPAND | wxALL, 5);
}

// Events
void WPPanel::OnHelp(wxCommandEvent& event)
{

}

void WPPanel::OnAddWorkout(wxCommandEvent& event)
{

}