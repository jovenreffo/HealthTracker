#include "Settings.h"

BEGIN_EVENT_TABLE(Settings, wxPanel)
	EVT_BUTTON(static_cast<int>(SE::ID_RESET_ALL), Settings::OnResetAll)
	EVT_BUTTON(static_cast<int>(SE::ID_RESET_ENTRIES), Settings::OnResetEntries)
	EVT_BUTTON(static_cast<int>(SE::ID_RESET_WORKOUTS), Settings::OnResetWorkouts)
	EVT_BUTTON(static_cast<int>(SE::ID_RESET_ROUTINES), Settings::OnResetRoutines)
	EVT_BUTTON(static_cast<int>(SE::ID_ADD_WORKOUT), Settings::OnAddWorkout)
	EVT_BUTTON(static_cast<int>(SE::ID_ADD_ROUTINE), Settings::OnAddRoutine)
	EVT_BUTTON(static_cast<int>(SE::ID_ADD_NUTR_ITEM), Settings::OnAddNutritionItem)
END_EVENT_TABLE()

Settings::Settings(ExerciseBook* pExerciseBook, Journal* pJournal, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style), m_pExerciseBook{ pExerciseBook }, m_pJournal { pJournal }
{
	this->Init();
	this->InitWindowPointers();
}

void Settings::Init()
{
	this->SetupSizers();
	this->AddAllControls();
}

void Settings::InitWindowPointers()
{
	m_pNutrBook = m_pExerciseBook->GetNutritionBook();
	m_pCaloriePanel = m_pNutrBook->GetCaloriePanel();
	m_WPNotebook = m_pExerciseBook->GetNotebook();
	m_pListbook = dynamic_cast<wxListbook*>(m_pJournal->GetParent()); // wxDynamicCast otherwise
}

void Settings::SetupControls()
{
	// Reset controls
	m_pResetAll = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_ALL), _T("Reset All"), wxDefaultPosition, wxDefaultSize);
	m_pResetEntries = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_ENTRIES), _T("Reset Entries"), wxDefaultPosition, wxDefaultSize);
	m_pResetWorkouts = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_WORKOUTS), _T("Reset Workouts"), wxDefaultPosition, wxDefaultSize);
	m_pResetRoutines = new wxButton(m_pTopParent, static_cast<int>(SE::ID_RESET_ROUTINES), _T("Reset Routines"), wxDefaultPosition, wxDefaultSize);

	// Add item controls
	m_pAddWorkout = new wxButton(m_pTopParent, static_cast<int>(SE::ID_ADD_WORKOUT), _T("Add Workout"));
	m_pAddRoutine = new wxButton(m_pTopParent, static_cast<int>(SE::ID_ADD_ROUTINE), _T("Add Routine"));
	m_pAddNutrItem = new wxButton(m_pTopParent, static_cast<int>(SE::ID_ADD_NUTR_ITEM), _T("Add Nutrition Item"));
}

void Settings::SetupSizers()
{
	// Set up the top level sizer
	m_pTopSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("Settings"));
	m_pTopParent = m_pTopSizer->GetStaticBox();
	this->SetSizerAndFit(m_pTopSizer);

	// Initialise the content sizers and controls before arranging the items
	m_pResetBox = new wxStaticBoxSizer(wxVERTICAL, m_pTopParent, _T("Reset Items"));
	m_pAddItemBox = new wxStaticBoxSizer(wxVERTICAL, m_pTopParent, _T("Add Items"));
	
	m_pTopSizer->Add(m_pResetBox, wxSizerFlags().Border(wxLEFT | wxALL, 5).Align(wxLEFT));
	m_pTopSizer->Add(m_pAddItemBox, wxSizerFlags().Border(wxALL, 5).Align(wxLEFT));

	this->SetupControls();
}

void Settings::AddAllControls()
{
	this->AddResetGroup();
	this->AddItemsGroup();
}

void Settings::AddResetGroup()
{
	wxBoxSizer* pResetSizer = new wxBoxSizer(wxVERTICAL);
	m_pResetBox->Add(pResetSizer);

	pResetSizer->Add(m_pResetAll, wxSizerFlags().Border(wxALL, 5));
	pResetSizer->Add(m_pResetEntries, wxSizerFlags().Border(wxALL, 5));
	pResetSizer->Add(m_pResetRoutines, wxSizerFlags().Border(wxALL, 5));
	pResetSizer->Add(m_pResetWorkouts, wxSizerFlags().Border(wxALL, 5));
}

void Settings::AddItemsGroup()
{
	wxBoxSizer* pAddItemsSizer = new wxBoxSizer(wxVERTICAL);
	m_pAddItemBox->Add(pAddItemsSizer);

	pAddItemsSizer->Add(m_pAddRoutine, wxSizerFlags().Border(wxALL, 5));
	pAddItemsSizer->Add(m_pAddWorkout, wxSizerFlags().Border(wxALL, 5));
	pAddItemsSizer->Add(m_pAddNutrItem, wxSizerFlags().Border(wxALL, 5));
}

// ====================================== Events ======================================

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
	{
		m_pJournal->GetEntryList()->ResetList();
		m_pListbook->SetSelection(0);
	}
}

void Settings::OnResetWorkouts(wxCommandEvent& WXUNUSED(event))
{
	if (ConfirmReset())
	{
		m_WPNotebook->GetWorkoutList()->ResetList();
		m_pListbook->SetSelection(1);
	}
}

void Settings::OnResetRoutines(wxCommandEvent& WXUNUSED(event))
{
	if (ConfirmReset())
	{
		m_WPNotebook->GetRoutineList()->ResetList();
		m_pListbook->SetSelection(1);
	}
}

void Settings::OnAddWorkout(wxCommandEvent& WXUNUSED(event))
{
	m_pListbook->SetSelection(1);
	m_pExerciseBook->SetSelection(0);
	m_WPNotebook->SetSelection(0);
	m_WPNotebook->CreateNewWorkout();
}

void Settings::OnAddRoutine(wxCommandEvent& WXUNUSED(event))
{
	m_pListbook->SetSelection(1);
	m_pExerciseBook->SetSelection(0);
	m_WPNotebook->SetSelection(0);
	m_WPNotebook->CreateNewRoutine();
}

void Settings::OnAddNutritionItem(wxCommandEvent& WXUNUSED(event))
{
	m_pListbook->SetSelection(1);
	m_pExerciseBook->SetSelection(1);
	m_pCaloriePanel->AddNewItem();
}

bool Settings::ConfirmReset()
{
	if (wxMessageBox(_T("Are you sure you want to reset this list?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		return true;
	else
		return false;
}
