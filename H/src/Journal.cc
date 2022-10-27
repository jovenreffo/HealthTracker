#include "Journal.h"

BEGIN_EVENT_TABLE(Journal, wxPanel)

END_EVENT_TABLE()

Journal::Journal(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void Journal::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void Journal::SetupControls()
{
	// Text
	m_pDateText = new wxStaticText(this, wxID_STATIC, _T("Date:"), wxDefaultPosition, wxDefaultSize);
	m_pMessageText = new wxStaticText(this, wxID_STATIC, _T("What is going on today?"), wxDefaultPosition, wxDefaultSize);
	m_pPrevEntryText = new wxStaticText(this, wxID_STATIC, _T("Previous Entries:"), wxDefaultPosition, wxDefaultSize);

	// Control classes
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	m_pEntryCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// Buttons



}

void Journal::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pDateSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(m_pTopSizer);
	m_pTopSizer->Add(m_pDateText, 0, wxLEFT | wxALL, 5);
	m_pTopSizer->Add(m_pMessageText, 0, wxLEFT | wxALL, 5);
	m_pTopSizer->Add(m_pTextCtrl, 1, wxEXPAND | wxALL, 5);
	m_pTopSizer->Add(m_pPrevEntryText, 0, wxLEFT | wxALL, 5);
	m_pTopSizer->Add(m_pEntryCtrl, 1, wxEXPAND | wxALL, 5);
}
