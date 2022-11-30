#include <wx/log.h>
#include <wx/valgen.h>
#include <wx/valtext.h>
#include "AddItemDlg.h"

BEGIN_EVENT_TABLE(AddItemDlg, wxDialog)
	EVT_UPDATE_UI(wxID_OK, AddItemDlg::OnUpdateOK)
	EVT_BUTTON(wxID_OK, AddItemDlg::OnOK)
	EVT_BUTTON(wxID_CANCEL, AddItemDlg::OnCancel)
	EVT_TEXT_ENTER(wxID_ANY, AddItemDlg::OnEnter)
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
	
	m_pFoodName = new wxTextCtrl(this, static_cast<int>(AID::ID_CALORIE_TEXT), wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(0, &m_itemName));

	// Initialize spin controls
	m_pCalories = new wxSpinCtrl(this, static_cast<int>(AID::ID_CALORIE_SPIN), _T("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000);
	m_pCalories->SetValidator(wxGenericValidator(&m_calorieContent)); // wxSpinCtrl does not take a validator in the ctor, so set it here.

	m_pCarbCtrl = new wxSpinCtrl(this, static_cast<int>(AID::ID_CARB_SPIN), _T("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000);
	m_pCarbCtrl->SetValidator(wxGenericValidator(&m_carbContent));

	m_pProteinCtrl = new wxSpinCtrl(this, static_cast<int>(AID::ID_PROTEIN_SPIN), _T("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000);
	m_pProteinCtrl->SetValidator(wxGenericValidator(&m_proteinContent));

	m_pFiberCtrl = new wxSpinCtrl(this, static_cast<int>(AID::ID_FIBER_SPIN), _T("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000);
	m_pFiberCtrl->SetValidator(wxGenericValidator(&m_fiberContent));
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
	m_pItemSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Calories:")), wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxLEFT, 5));
	m_pItemSizer->Add(m_pCalories, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxLEFT, 25));
	m_pTopSizer->Add(m_pItemSizer);

	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Proportion(0).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticText(this, wxID_STATIC, _T("(Optional) Enter any other nutritional information about the item:")),
		wxSizerFlags().Proportion(0).Expand().Border(wxALL, 5));

	m_pItemSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pItemSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Carbohydrates:")), wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxALL, 5));
	m_pItemSizer->Add(m_pCarbCtrl, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxLEFT, 5));
	m_pTopSizer->Add(m_pItemSizer);

	m_pItemSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pItemSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Protein:")), wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxALL, 5));
	m_pItemSizer->Add(m_pProteinCtrl, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxLEFT, 44));
	m_pTopSizer->Add(m_pItemSizer);

	m_pItemSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pItemSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Fiber:")), wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxALL, 5));
	m_pItemSizer->Add(m_pFiberCtrl, wxSizerFlags().Proportion(0).Align(wxALIGN_LEFT).Border(wxLEFT, 56));
	m_pTopSizer->Add(m_pItemSizer);

	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Proportion(0).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer);
}

void AddItemDlg::HandleExit()
{
	m_total.m_calTotal = m_calorieContent;
	m_total.m_carbTotal = m_carbContent;
	m_total.m_proteinTotal = m_proteinContent;
	m_total.m_fiberTotal = m_fiberContent;

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

// Events

void AddItemDlg::OnUpdateOK(wxUpdateUIEvent& event)
{
	if (m_pCalories->GetValue() && !m_pFoodName->IsEmpty())
		event.Enable(true);
	else
		event.Enable(false);
}

void AddItemDlg::OnEnter(wxCommandEvent& event)
{
	this->HandleExit();
}

void AddItemDlg::OnOK(wxCommandEvent& event)
{
	this->HandleExit();
}

void AddItemDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

void AddItemDlg::OnSpinUp(wxSpinEvent& event)
{
	if (event.GetEventType() == wxEVT_SPIN_UP)
		m_pCalories->SetValue(m_pCalories->GetValue() + 25);
}