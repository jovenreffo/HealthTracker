#include "Settings.h"

BEGIN_EVENT_TABLE(Settings, wxPanel)

END_EVENT_TABLE()

Settings::Settings(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void Settings::Init()
{
	this->SetupSizers();
	this->AddAllControls();
}

void Settings::SetupControls()
{
	m_pResetAll = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_ALL), _T("Reset All"), wxDefaultPosition, wxDefaultSize);
	m_pResetWorkouts = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_WORKOUTS), _T("Reset Workouts"), wxDefaultPosition, wxDefaultSize);
	m_pResetRoutines = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_ROUTINES), _T("Reset Workouts"), wxDefaultPosition, wxDefaultSize);
}

void Settings::SetupSizers()
{
	// Set up the top level sizer
	m_pTopSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("Settings"));
	m_pTopParent = m_pTopSizer->GetStaticBox();
	m_pTopSizer->Layout();
	this->SetSizerAndFit(m_pTopSizer);

	// Initialise the content sizers and controls before arranging the items
	m_pResetBox = new wxStaticBoxSizer(wxVERTICAL, m_pTopParent, _T("Reset Items"));
	
	m_pTopSizer->Add(m_pResetBox, 0, wxALIGN_LEFT | wxALL, 5);

	this->SetupControls();
}

void Settings::AddAllControls()
{
	this->AddResetGroup();
}

void Settings::AddResetGroup()
{
	m_pResetBox->Add(m_pResetAll, 0, wxALIGN_LEFT | wxALL, 5);
	m_pResetBox->Add(m_pResetWorkouts, 0, wxALIGN_LEFT | wxALL, 5);
	m_pResetBox->Add(m_pResetRoutines, 0, wxALIGN_LEFT | wxALL, 5);

}
