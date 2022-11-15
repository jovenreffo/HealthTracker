#include <wx/sizer.h>
#include <wx/msgdlg.h>
#include "SaveWorkoutDialog.h"

BEGIN_EVENT_TABLE(SaveWorkoutDialog, wxDialog)
	EVT_BUTTON(wxID_OK, SaveWorkoutDialog::OnOK)
END_EVENT_TABLE()

SaveWorkoutDialog::SaveWorkoutDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
	this->SetMinSize(SWDIALOG_SIZE);
	this->SetInitialSize(SWDIALOG_SIZE);
	this->SetMaxSize(SWDIALOG_SIZE_MAX);
}

void SaveWorkoutDialog::Init()
{
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	m_pNameText = new wxStaticText(this, wxID_STATIC, _T("Workout name:"));
	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"));

	m_pTextCtrl->Bind(wxEVT_TEXT_ENTER, &SaveWorkoutDialog::OnEnter, this);

	this->SetupControls();
}

void SaveWorkoutDialog::SetupControls()
{
	wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* pTextSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(pTopSizer);

	pTextSizer->Add(m_pNameText, 0, wxALIGN_CENTRE_VERTICAL | wxALL, 5);
	pTextSizer->Add(m_pTextCtrl, 0, wxALIGN_CENTRE_VERTICAL | wxALL, 5);

	pButtonSizer->Add(m_pOk, 0, wxALIGN_CENTRE_VERTICAL | wxALL, 5);
	pButtonSizer->Add(m_pCancel, 0, wxALIGN_CENTRE_VERTICAL | wxALL, 5);

	pTopSizer->Add(pTextSizer);
	pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	pTopSizer->Add(pButtonSizer);
}

void SaveWorkoutDialog::OnOK(wxCommandEvent& event)
{
	// set the value of our wxString member to what the user has entered for later use
	m_textValue = m_pTextCtrl->GetValue();

	if (Validate() && TransferDataFromWindow())
	{
		if (IsModal())
			EndModal(wxID_OK);
		else
		{
			SetReturnCode(wxID_OK);
			this->Show(false);
		}
	}
}

void SaveWorkoutDialog::OnEnter(wxCommandEvent& event)
{
	m_textValue = m_pTextCtrl->GetValue();

	this->SetReturnCode(wxID_OK);
	this->Show(false);
	//event.Skip();
}
