#include <wx/msgdlg.h>
#include <wx/datetime.h>
#include "EntryDialog.h"

BEGIN_EVENT_TABLE(EntryDialog, wxDialog)
	EVT_BUTTON(wxID_OK, EntryDialog::OnOK)
	EVT_CHECKBOX(wxID_ANY, EntryDialog::OnCheck)
END_EVENT_TABLE()

EntryDialog::EntryDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
	this->SetupSizes();
}

void EntryDialog::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void EntryDialog::SetupSizes()
{
	this->SetMinSize(ENTRY_DIALOG_SIZE);
	this->SetInitialSize(ENTRY_DIALOG_SIZE);
	this->SetMaxSize(ENTRY_DIALOG_MAXSIZE);
}

void EntryDialog::SetupControls()
{
	m_pOkButton = new wxButton(this, wxID_OK, _T("OK"));
	m_pUseDate = new wxCheckBox(this, wxID_ANY, _T("Use today's date"));
	m_pCancelButton = new wxButton(this, wxID_CANCEL, _T("Cancel"));
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_pNameText = new wxStaticText(this, wxID_STATIC, _T("Entry name:"));
}

void EntryDialog::SetupSizers()
{
	// Initialisation
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pNameSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(m_pTopSizer);

	// name sizer
	m_pNameSizer->Add(m_pNameText, 0, wxLEFT | wxALL, 5);
	m_pNameSizer->Add(m_pTextCtrl, 0, wxLEFT | wxTOP, 5);

	// button sizer
	m_pButtonSizer->Add(m_pOkButton, 0, wxLEFT | wxALL, 5);
	m_pButtonSizer->Add(m_pCancelButton, 0, wxLEFT | wxALL, 5);

	// arrange sizers accordingly
	m_pTopSizer->Add(m_pNameSizer);
	m_pTopSizer->Add(m_pUseDate, 0, wxLEFT | wxALL, 5);
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	m_pTopSizer->Add(m_pButtonSizer);
}

wxString EntryDialog::GetDate()
{
	wxDateTime dt;
	dt.SetToCurrent();
	return dt.FormatDate();
}

void EntryDialog::OnOK(wxCommandEvent& event)
{
	// Set the member string for use
	m_entryName = m_pTextCtrl->GetValue();

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

void EntryDialog::OnCheck(wxCommandEvent& event)
{
	if (event.IsChecked())
		m_pTextCtrl->SetValue(GetDate());
	else // Reset the text control's value if the user unselects it. Saves them time deleting it.
		m_pTextCtrl->SetValue(wxEmptyString);
}
