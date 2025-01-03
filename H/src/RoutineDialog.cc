#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/valtext.h>
#include <wx/valgen.h>

#include "RoutineDialog.h"
#include "StandardPath.hpp"

// Choice

Choice::Choice(int uniqueID, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style)
	: wxChoice(parent, id, pos, size, choices, style), m_uniqueID{ uniqueID }
{
	this->Bind(wxEVT_CHOICE, &Choice::OnChoice, this);
}

Choice::~Choice()
{
	this->Unbind(wxEVT_CHOICE, &Choice::OnChoice, this);
}

void Choice::OnChoice(wxCommandEvent& event)
{
#ifdef _DEBUG
	wxLogMessage(_("%d\n%s"), m_uniqueID, this->GetStringSelection());
#endif
}

// RoutineDialog

BEGIN_EVENT_TABLE(RoutineDialog, wxDialog)
	EVT_BUTTON(wxID_OK, RoutineDialog::OnOK)
	EVT_CLOSE(RoutineDialog::OnClose)
	EVT_TEXT_ENTER(wxID_ANY, RoutineDialog::OnEnter)
END_EVENT_TABLE()

RoutineDialog::RoutineDialog(const std::vector<EntryContent>& content, WorkoutList* pWorkoutList, RoutineList* pRoutineList, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog{ parent, id, title, pos, size, style }, m_content{ content }, m_pWorkoutList{ pWorkoutList }, m_pRoutineList { pRoutineList }
{
	this->Init();
}

RoutineDialog::~RoutineDialog()
{
	// Unbind events from the choice
	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
	{
		m_pChoice[i]->Unbind(wxEVT_CHOICE, &RoutineDialog::OnChoice, this);
	}
}

void RoutineDialog::Init()
{
	this->CreateControls();
	this->SetupControls();
	this->SetupSizing();
}

void RoutineDialog::SetupSizing()
{
	this->SetMinSize(RDLG_SIZE);
	this->SetInitialSize(RDLG_SIZE);
	//this->SetMaxSize(RDLG_MAX_SIZE);
}

void RoutineDialog::SetupControls()
{
	// Sizers
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pDayFlexSizer = new wxFlexGridSizer(3, wxSize(5, 1));

	this->SetSizerAndFit(m_pTopSizer);

	// For each day
	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
	{
		// re-initialise the button for each day of week being added
		// otherwise wx will throw an error saying a window is being added to multiple sizers
		m_viewButtonArr[i] = new ViewButton(m_pWorkoutList, m_pChoice[i]->GetStringSelection(), m_pChoice[i]->GetSelection(), i, this, (int)RD::ID_VIEW, wxBitmap(path_data::dataDir + _T("\\Images\\view.png"), wxBITMAP_TYPE_PNG), wxDefaultPosition, wxDefaultSize);

		m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, m_daysOfWeek[i]), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
		m_pDayFlexSizer->Add(m_pChoice[i], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));
		m_pDayFlexSizer->Add(m_viewButtonArr[i], wxSizerFlags().Border(wxALL, 5));
	}

	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Name:")), wxSizerFlags().Proportion(0).Left().Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pTextCtrl, wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));
	m_pDayFlexSizer->AddSpacer(5);

	m_pTopSizer->Add(m_pDayFlexSizer, wxSizerFlags().CentreHorizontal());

	// Separate the choices and buttons
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);

	m_pDayFlexSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pDayFlexSizer->Add(m_pOk, wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pCancel, wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE).Border(wxALL, 5));
	m_pTopSizer->Add(m_pDayFlexSizer, wxSizerFlags().CentreHorizontal());
}

void RoutineDialog::CreateControls()
{
	// Initialise the choice array
	for (auto i{ 0 }; i < m_content.size(); ++i)
		m_choiceArray.Add(m_content[i].GetName());
	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
	{
		m_pChoice[i] = new Choice(i, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceArray, wxCB_SORT);

		// Bind OnChoice event
		m_pChoice[i]->Bind(wxEVT_CHOICE, &RoutineDialog::OnChoice, this);
	}

	// Days of week
	m_daysOfWeek.Add(_T("Sunday"));
	m_daysOfWeek.Add(_T("Monday"));
	m_daysOfWeek.Add(_T("Tuesday"));
	m_daysOfWeek.Add(_T("Wednesday"));
	m_daysOfWeek.Add(_T("Thursday"));
	m_daysOfWeek.Add(_T("Friday"));
	m_daysOfWeek.Add(_T("Saturday"));

	// Buttons
	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	// Textctrl
	m_pTextCtrl = new wxTextCtrl(this, static_cast<int>(RD::ID_ROUTINE_NAME), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NONE, &m_routineName));
	m_pTextCtrl->Bind(wxEVT_TEXT_ENTER, &RoutineDialog::OnEnter, this);
}

void RoutineDialog::OpenRoutine()
{
	// Loop through the choice array.
	// Set up corresponding strings.
	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
	{
		m_pChoice[i]->SetStringSelection(m_routine.m_daysOfWeek[i]);
	}
}

void RoutineDialog::HandleExit()
{

	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
	{
		m_routine.m_daysOfWeek[i] = m_pChoice[i]->GetStringSelection();
	}

	m_pRoutineList->AddItem(m_routineName, m_routine);
}

// events

void RoutineDialog::OnOK(wxCommandEvent& WXUNUSED(event))
{
	if (Validate() && TransferDataFromWindow())
	{
		this->HandleExit();

		if (IsModal())
			EndModal(wxID_OK);
		else
		{
			this->SetReturnCode(wxID_OK);
			this->Show(false);
		}
	}
}

void RoutineDialog::OnClose(wxCloseEvent& WXUNUSED(event))
{
	this->Destroy();
}

void RoutineDialog::OnEnter(wxCommandEvent& WXUNUSED(event))
{
	this->HandleExit();

	this->SetReturnCode(wxID_OK);
	this->Show(false);
}

void RoutineDialog::OnChoice(wxCommandEvent& WXUNUSED(event))
{
	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
	{
		// Re-initialize the workout name for each selection, so all get updated at once.
		m_viewButtonArr[i]->SetWorkoutName(m_pChoice[i]->GetStringSelection());
	}
}