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
	m_pHelpButton = new wxButton(this, wxID_HELP, _T("Help"), wxDefaultPosition, wxDefaultSize);
	m_pAddWorkoutButton = new wxButton(this, wxID_ADD, _T("Add Workout"), wxDefaultPosition, wxDefaultSize);

}

void WPPanel::SetupSizers()
{
}

// Events
void WPPanel::OnHelp(wxCommandEvent& event)
{

}

void WPPanel::OnAddWorkout(wxCommandEvent& event)
{

}