#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/valtext.h>
#include "RoutineDialog.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(RoutineDialog, wxDialog)
	EVT_BUTTON(wxID_OK, RoutineDialog::OnOK)
	EVT_CLOSE(RoutineDialog::OnClose)
	EVT_TEXT_ENTER(wxID_ANY, RoutineDialog::OnEnter)
END_EVENT_TABLE()

RoutineDialog::RoutineDialog(const std::vector<EntryContent>& content, RoutineList* pRoutineList, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog{ parent, id, title, pos, size, style }, m_content{ content }, m_pRoutineList{ pRoutineList }
{
	this->Init();
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
	this->SetMaxSize(RDLG_MAX_SIZE);
}

void RoutineDialog::SetupControls()
{
	// Sizers
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pDayFlexSizer = new wxFlexGridSizer(3, wxSize(5, 1));

	this->SetSizerAndFit(m_pTopSizer);
	m_pTopSizer->Add(m_pDayFlexSizer, wxSizerFlags().CentreHorizontal());

	// For each day
	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Sunday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pChoice[0], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));
	m_pDayFlexSizer->Add(m_pView, wxSizerFlags().Border(wxALL, 5));

	m_pDayFlexSizer = new wxFlexGridSizer(2, wxSize(5, 1));

	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Monday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pChoice[1], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));

	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Tuesday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pChoice[2], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));

	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Wednesday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pChoice[3], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));

	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Thursday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pChoice[4], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));

	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Friday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pChoice[5], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));

	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Saturday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pChoice[6], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));

	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Name:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pTextCtrl, wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));

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
		m_pChoice[i] = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceArray, wxCB_SORT);

	// Buttons
	m_pView = new wxBitmapButton(this, wxID_ANY, wxBitmap(path_data::dataDir + _T("\\Images\\view.png"), wxBITMAP_TYPE_PNG), wxDefaultPosition, wxDefaultSize);
	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	// Textctrl
	m_pTextCtrl = new wxTextCtrl(this, static_cast<int>(RD::ID_ROUTINE_NAME), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NONE, &m_routineName));
	m_pTextCtrl->Bind(wxEVT_TEXT_ENTER, &RoutineDialog::OnEnter, this);
}

void RoutineDialog::HandleExit()
{
	Routine r;

	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
	{
		r.m_daysOfWeek[i] = m_pChoice[i]->GetStringSelection();
	}

	m_pRoutineList->AddItem(m_routineName, r);
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
