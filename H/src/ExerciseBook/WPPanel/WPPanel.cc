#include <wx/statline.h>
#include "WPPanel.h"

BEGIN_EVENT_TABLE(WPPanel, wxPanel)
	EVT_BUTTON(wxID_HELP, WPPanel::OnHelp)
END_EVENT_TABLE()

WPPanel::WPPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxSplitterWindow(parent, id, pos, size, style)
{
	this->Init();
}

void WPPanel::Init()
{
	this->SetupControls();
}

void WPPanel::SetupControls()
{
	m_pWorkoutList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pRoutineList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	m_pHelpButton = new wxButton(this, wxID_HELP, _T("Help"), wxDefaultPosition, wxDefaultSize);
	m_pAddWorkoutButton = new wxButton(this, wxID_ADD, _T("Add Workout"), wxDefaultPosition, wxDefaultSize);
}

// Events
void WPPanel::OnHelp(wxCommandEvent& event)
{

}

void WPPanel::OnAddWorkout(wxCommandEvent& event)
{

}