#include "RoutineDialog.h"

BEGIN_EVENT_TABLE(RoutineDialog, wxDialog)
EVT_BUTTON(wxID_OK, RoutineDialog::OnOK)
EVT_CLOSE(RoutineDialog::OnClose)
END_EVENT_TABLE()

RoutineDialog::RoutineDialog(const std::vector<EntryContent>& content, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog{ parent, id, title, pos, size, style }, m_content{ content }
{
	this->Init();
}

void RoutineDialog::Init()
{
	this->CreateControls();
	this->SetupControls();
	this->SetupSizing();
}

void RoutineDialog::RetrieveAllNames()
{

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

	// For each day
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Sunday:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_pDaySizer->Add(m_pChoice[0], 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 27);
	m_pTopSizer->Add(m_pDaySizer, 0, wxALIGN_LEFT);

	// Re-init the sizer
	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Monday:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_pDaySizer->Add(m_pChoice[1], 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 22);
	m_pTopSizer->Add(m_pDaySizer, 0, wxALIGN_LEFT);

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Tuesday:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_pDaySizer->Add(m_pChoice[2], 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 23);
	m_pTopSizer->Add(m_pDaySizer, 0, wxALIGN_LEFT);

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Wednesday:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_pDaySizer->Add(m_pChoice[3], 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
	m_pTopSizer->Add(m_pDaySizer, 0, wxALIGN_LEFT);

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Thursday:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_pDaySizer->Add(m_pChoice[4], 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 18);
	m_pTopSizer->Add(m_pDaySizer, 0, wxALIGN_LEFT);

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Friday:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_pDaySizer->Add(m_pChoice[5], 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 34);
	m_pTopSizer->Add(m_pDaySizer, 0, wxALIGN_LEFT);

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Saturday:")), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_pDaySizer->Add(m_pChoice[6], 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 20);
	m_pTopSizer->Add(m_pDaySizer, 0, wxALIGN_LEFT);

	// Separate the choices and buttons
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);

	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	m_pDaySizer->Add(m_pOk, 0, wxALIGN_CENTRE | wxALL, 5);
	m_pDaySizer->Add(m_pCancel, 0, wxALIGN_CENTRE | wxALL, 5);
	m_pTopSizer->Add(m_pDaySizer, 0, wxALIGN_CENTRE);
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
}

// events

void RoutineDialog::OnOK(wxCommandEvent& WXUNUSED(event))
{
}

void RoutineDialog::OnClose(wxCloseEvent& WXUNUSED(event))
{
	this->Destroy();
}