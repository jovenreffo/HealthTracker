#include "RoutineView.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(RoutineView, wxDialog)

END_EVENT_TABLE()

RoutineView::RoutineView(long selectionIndex, const Routine& routine, const std::vector<EntryContent>& content, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_selectionIndex{ selectionIndex }, m_content{ content }, m_routine{ routine }
{
	this->Init();
}

void RoutineView::Init()
{
	this->SetupControls();
	this->CreateControls();
	this->SetupSizing();
	this->SetupSelections();
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
	m_pTopSizer->Add(m_pDayFlexSizer, wxSizerFlags().CentreHorizontal());

	// For each day
	m_pDayFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Sunday:")), wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE_VERTICAL).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pChoice[0], wxSizerFlags().Proportion(0).CentreVertical().Border(wxLEFT, 5));

	// Re-init the sizer
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

	// Separate the choices and buttons
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);

	m_pDayFlexSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pDayFlexSizer->Add(m_pOk, wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE).Border(wxALL, 5));
	m_pDayFlexSizer->Add(m_pCancel, wxSizerFlags().Proportion(0).Align(wxALIGN_CENTRE).Border(wxALL, 5));
	m_pTopSizer->Add(m_pDayFlexSizer, wxSizerFlags().CentreHorizontal());
}

void RoutineView::SetupControls()
{
	// Initialise the choice array
	for (auto i{ 0 }; i < m_content.size(); ++i)
		m_choiceArray.Add(m_content[i].GetName());
	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
		m_pChoice[i] = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceArray, wxCB_SORT);

	// Buttons
	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
	m_viewBmp = wxBitmap(path_data::dataDir + _T("\\Images\\view.png"), wxBITMAP_TYPE_PNG);
	m_pViewButton = new wxBitmapButton(this, wxID_ANY, m_viewBmp, wxDefaultPosition, wxDefaultSize);

	// Textctrl
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	m_pTextCtrl->Bind(wxEVT_TEXT_ENTER, &RoutineView::OnEnter, this);

	// Sizers initialization
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pDayFlexSizer = new wxFlexGridSizer(2, wxSize(5, 1));
}

void RoutineView::SetupSelections()
{
	// loop through the choice array
	// set the corresponding controls to the correct string values
	for (auto i{ 0 }; i < ROUTINE_LIST_SIZE; ++i)
	{
		m_pChoice[i]->SetStringSelection(m_routine.m_daysOfWeek[i]);
	}
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
