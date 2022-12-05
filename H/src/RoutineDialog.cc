#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/valtext.h>
#include "RoutineDialog.h"

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
	this->SetSizerAndFit(m_pTopSizer);
	m_pDayFlexSizer = new wxFlexGridSizer(2, wxSize(5, 1));


	// For each day
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Sunday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDaySizer->Add(m_pChoice[0], wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxLEFT, 27));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT));

	// Re-init the sizer
	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Monday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDaySizer->Add(m_pChoice[1], wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxLEFT, 22));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT));

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Tuesday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDaySizer->Add(m_pChoice[2], wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxLEFT, 23));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT));

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Wednesday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDaySizer->Add(m_pChoice[3], wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxLEFT, 5));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT));

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Thursday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDaySizer->Add(m_pChoice[4], wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxLEFT, 18));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT));

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Friday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDaySizer->Add(m_pChoice[5], wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxLEFT, 34));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT));

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Saturday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDaySizer->Add(m_pChoice[6], wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxLEFT, 20));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT));

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Name:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDaySizer->Add(m_pTextCtrl, wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxLEFT, 34));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT));

	// Separate the choices and buttons
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(m_pOk, wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE).Border(wxALL, 5));
	m_pDaySizer->Add(m_pCancel, wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE).Border(wxALL, 5));
	m_pTopSizer->Add(m_pDaySizer, wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE).Border(wxALL, 5));
}

void RoutineDialog::CreateControls()
{
	// Initialise the choice array
	for (auto i{ 0 }; i < m_content.size(); ++i)
		m_choiceArray.Add(m_content[i].GetName());
	for (auto i{ 0 }; i < CL_SIZE; ++i)
		m_pChoice[i] = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceArray, wxCB_SORT);

	// Buttons
	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	// Sizers
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);

	// Textctrl
	m_pTextCtrl = new wxTextCtrl(this, static_cast<int>(RD::ID_ROUTINE_NAME), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NONE, &m_routineName));
	m_pTextCtrl->Bind(wxEVT_TEXT_ENTER, &RoutineDialog::OnEnter, this);
}

void RoutineDialog::HandleExit()
{
	Routine r;
	for (auto i{ 0 }; i < CL_SIZE; ++i)
	{
		// store the selected workout at index i in the current routine
		r.m_pairs[i] = { i, m_pChoice[i]->GetStringSelection() };
		m_routineInfo.push_back(r);
	}

	// get the value the user input to the text ctrl
	m_routineName = m_pTextCtrl->GetValue();
	m_pRoutineList->AddItem(m_routineName, r);
}

// events

void RoutineDialog::OnOK(wxCommandEvent& WXUNUSED(event))
{
	this->HandleExit();

	if (Validate() && TransferDataFromWindow())
	{
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
