#include "RoutineView.h"

BEGIN_EVENT_TABLE(RoutineView, wxDialog)


END_EVENT_TABLE()

RoutineView::RoutineView(const std::vector<Routine>& routineInfo, const std::vector<EntryContent>& content, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_routineInfo{ routineInfo }, m_content{ content }
{
	this->Init();
}

void RoutineView::Init()
{
	this->SetupControls();
	this->CreateControls();
	this->SetupSizing();
}

void RoutineView::SetupSizing()
{
	this->SetMinSize(RVDLG_SIZE);
	this->SetMaxSize(RVDLG_MAX_SIZE);
	this->SetInitialSize(RVDLG_SIZE);
}

void RoutineView::CreateControls()
{
	this->SetSizerAndFit(m_pTopSizer);

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

void RoutineView::SetupControls()
{
	// Initialise the choice array
	for (auto i{ 0 }; i < m_routineInfo.size(); ++i)
		m_choiceArray.Add(m_routineInfo[i].GetStringAt(i));
	for (auto i{ 0 }; i < CL_SIZE; ++i)
		m_pChoice[i] = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceArray, wxCB_SORT);

	// Buttons
	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);

	// Sizers
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);

	// Textctrl
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	m_pTextCtrl->Bind(wxEVT_TEXT_ENTER, &RoutineView::OnEnter, this);
}

void RoutineView::OnOK(wxCommandEvent& event)
{
}

void RoutineView::OnEnter(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_OK);
	this->Show(false);
}

void RoutineView::OnClose(wxCloseEvent& event)
{
	this->Destroy();
}