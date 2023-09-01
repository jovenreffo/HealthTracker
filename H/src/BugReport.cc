#include <wx/config.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include "BugReport.h"
#include "StandardPath.hpp"

BugReport::BugReport(PrefsDlg* pPrefsDlg, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_pPrefsDlg{ pPrefsDlg }
{
	this->Init();
	this->LoadConfig();

	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &BugReport::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &BugReport::OnCancel, this, wxID_CANCEL);

	m_pModifyBtn[0]->Bind(wxEVT_BUTTON, &BugReport::OnModify, this);
	m_pModifyBtn[1]->Bind(wxEVT_BUTTON, &BugReport::OnModify, this);
}

BugReport::~BugReport()
{
	// unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &BugReport::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &BugReport::OnCancel, this, wxID_CANCEL);

	m_pModifyBtn[0]->Unbind(wxEVT_BUTTON, &BugReport::OnModify, this);
	m_pModifyBtn[1]->Unbind(wxEVT_BUTTON, &BugReport::OnModify, this);
}

void BugReport::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void BugReport::LoadConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/Preferences/"));

	// Read the values
	m_name = pConfig->Read(_T("UserName"), wxEmptyString);
	m_email = pConfig->Read(_T("UserEmail"), wxEmptyString);

	// write them to the text controls
	m_pNameTxt->SetValue(m_name);
	m_pEmailTxt->SetValue(m_email);
}

void BugReport::SetupControls()
{
	m_pModifyBtn[0] = new wxBitmapButton(this, wxID_ANY, wxBitmap(path_data::dataDir + _T("\\Images\\modify2.png"), wxBITMAP_TYPE_PNG));
	m_pModifyBtn[0]->SetToolTip(_T("Edit name."));

	m_pModifyBtn[1] = new wxBitmapButton(this, wxID_ANY, wxBitmap(path_data::dataDir + _T("\\Images\\modify2.png"), wxBITMAP_TYPE_PNG));
	m_pModifyBtn[1]->SetToolTip(_T("Edit email."));

	m_pNameTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_pEmailTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_pReportTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2);

	m_pOk = new wxButton(this, wxID_OK, _T("Send"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
}

void BugReport::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pControlSizer = new wxFlexGridSizer(3, wxSize(5, 1));
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);
	
	// name
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Name:")), wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pControlSizer->Add(m_pNameTxt, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pControlSizer->Add(m_pModifyBtn[0], wxSizerFlags().CentreVertical().Border(wxALL, 5));

	// email
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Email:")), wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pControlSizer->Add(m_pEmailTxt, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pControlSizer->Add(m_pModifyBtn[1], wxSizerFlags().CentreVertical().Border(wxALL, 5));
	
	// main text box
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Message:")), wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pControlSizer->Add(m_pReportTxt, wxSizerFlags().Proportion(1).Expand().Left().Border(wxALL, 5));
	m_pControlSizer->AddSpacer(5);
	m_pTopSizer->Add(m_pControlSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Left().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal());
}

void BugReport::SetupSizing()
{
	wxSize size = this->GetBestSize();
	wxSize initial = wxSize(size.x + 50, size.y + 35);

	this->SetMinSize(size);
	this->SetInitialSize(initial);
}

void BugReport::OnModify(wxCommandEvent& event)
{
	m_pPrefsDlg->Show(this);

}

void BugReport::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void BugReport::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}
