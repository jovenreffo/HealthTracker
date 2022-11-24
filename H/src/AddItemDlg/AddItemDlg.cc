#include <wx/log.h>
#include "AddItemDlg.h"

BEGIN_EVENT_TABLE(AddItemDlg, wxDialog)
	EVT_BUTTON(wxID_OK, AddItemDlg::OnOK)
	EVT_BUTTON(wxID_CANCEL, AddItemDlg::OnCancel)
END_EVENT_TABLE()

AddItemDlg::AddItemDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
}

void AddItemDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void AddItemDlg::SetupSizing()
{
	this->SetMinSize(ADDITEMDLG_SIZE);
	this->SetInitialSize(ADDITEMDLG_SIZE);
	this->SetMaxSize(ADDITEMDLG_MAX);
}

void AddItemDlg::SetupControls()
{
	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);

	m_pFoodName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_pCalories = new wxSpinCtrl(this, wxID_ANY, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 10000);
}

void AddItemDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pItemSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Proportion(0).Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Proportion(0).Border(wxALL, 5));

	m_pItemSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Item name:")), wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxALL, 5));
	m_pItemSizer->Add(m_pFoodName, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxLEFT, 5));
	m_pTopSizer->Add(m_pItemSizer);

	m_pItemSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pItemSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Calories:")), wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxALL, 5));
	m_pItemSizer->Add(m_pCalories, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxALL, 5));
	m_pTopSizer->Add(m_pItemSizer);

	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Proportion(0).Expand().Border(wxLEFT, 5));
	m_pTopSizer->Add(m_pButtonSizer);
}

// Events

void AddItemDlg::OnOK(wxCommandEvent& event)
{
	// Get the values the user entered
	m_itemName = m_pFoodName->GetValue();
	m_calorieContent = m_pCalories->GetValue();

#ifdef _DEBUG
	wxLogMessage("%s\n%d",
		m_itemName,
		m_calorieContent);
#endif

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

void AddItemDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}