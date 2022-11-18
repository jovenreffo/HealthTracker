#include "Settings.h"

BEGIN_EVENT_TABLE(Settings, wxPanel)
	EVT_BUTTON(static_cast<int>(SE::ID_RESET_ALL), Settings::OnResetAll)
	EVT_BUTTON(static_cast<int>(SE::ID_RESET_ENTRIES), Settings::OnResetEntries)
	EVT_BUTTON(static_cast<int>(SE::ID_RESET_WORKOUTS), Settings::OnResetWorkouts)
	EVT_BUTTON(static_cast<int>(SE::ID_RESET_ROUTINES), Settings::OnResetRoutines)
END_EVENT_TABLE()

Settings::Settings(ExercisePanel* pExercisePanel, Journal* pJournal, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style), m_pExercisePanel{ pExercisePanel }, m_pJournal{ pJournal }
{
	this->Init();
	m_WPNotebook = m_pExercisePanel->GetExerciseBook()->GetNotebook();
}

void Settings::Init()
{
	this->SetupSizers();
	this->AddAllControls();
}

void Settings::SetupControls()
{
	m_pResetAll = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_ALL), _T("Reset All"), wxDefaultPosition, wxDefaultSize);
	m_pResetEntries = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_ENTRIES), _T("Reset Entries"), wxDefaultPosition, wxDefaultSize);
	m_pResetWorkouts = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_WORKOUTS), _T("Reset Workouts"), wxDefaultPosition, wxDefaultSize);
	m_pResetRoutines = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_ROUTINES), _T("Reset Routines"), wxDefaultPosition, wxDefaultSize);
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
	
	m_pTopSizer->Add(m_pResetBox, wxSizerFlags().Border(wxLEFT | wxALL, 5).Align(wxLEFT));

	this->SetupControls();
}

void Settings::AddAllControls()
{
	this->AddResetGroup();
}

void Settings::AddResetGroup()
{
	wxBoxSizer* pResetSizer = new wxBoxSizer(wxVERTICAL);
	m_pResetBox->Add(pResetSizer);

	pResetSizer->Add(m_pResetAll, wxSizerFlags().Border(wxALIGN_LEFT | wxALL, 5));
	pResetSizer->Add(m_pResetEntries, wxSizerFlags().Border(wxALIGN_LEFT | wxALL, 5));
	pResetSizer->Add(m_pResetRoutines, wxSizerFlags().Border(wxALIGN_LEFT | wxALL, 5));
	pResetSizer->Add(m_pResetWorkouts, wxSizerFlags().Border(wxALIGN_LEFT | wxALL, 5));
}

void Settings::OnResetAll(wxCommandEvent& WXUNUSED(event))
{
	if (wxMessageBox(_T("Are you sure you want to delete all of your saved items?"), _T("Confirm"), wxYES_NO | wxICON_WARNING) == wxYES)
	{
		m_pJournal->GetEntryList()->ResetList();
		m_WPNotebook->GetWorkoutList()->ResetList();
		m_WPNotebook->GetRoutineList()->ResetList();
	}
}

void Settings::OnResetEntries(wxCommandEvent& WXUNUSED(event))
{
	if (ConfirmReset())
		m_pJournal->GetEntryList()->ResetList();
}

void Settings::OnResetWorkouts(wxCommandEvent& WXUNUSED(event))
{
	if (ConfirmReset())
		m_WPNotebook->GetWorkoutList()->ResetList();
}

void Settings::OnResetRoutines(wxCommandEvent& WXUNUSED(event))
{
	if (ConfirmReset())
		m_WPNotebook->GetRoutineList()->ResetList();
}

bool Settings::ConfirmReset()
{
	if (wxMessageBox(_T("Are you sure you want to reset this list?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		return true;
	else
		return false;
}
