#include <wx/log.h>
#include <wx/valgen.h>
#include <wx/valtext.h>

#include "AddItemDlg.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(AddItemDlg, wxDialog)
	EVT_UPDATE_UI(wxID_OK, AddItemDlg::OnUpdateOK)
	EVT_BUTTON(wxID_OK, AddItemDlg::OnOK)
	EVT_BUTTON(wxID_CANCEL, AddItemDlg::OnCancel)
	EVT_TEXT_ENTER(wxID_ANY, AddItemDlg::OnEnter)
END_EVENT_TABLE()

AddItemDlg::AddItemDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style, _T("additemdlg"))
{
	this->Init();

	// bind events
	m_pEnableMacros->Bind(wxEVT_UPDATE_UI, &AddItemDlg::OnUpdateControls, this);
}

AddItemDlg::~AddItemDlg()
{
	// unbind events
	m_pEnableMacros->Unbind(wxEVT_UPDATE_UI, &AddItemDlg::OnUpdateControls, this);
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
	m_pEnableMacros = new wxCheckBox(this, wxID_ANY, _T("Include other macros"), wxDefaultPosition, wxDefaultSize, 0L, wxGenericValidator(&m_bEnableMacros));

	m_searchBmp = wxBitmap(path_data::dataDir + _T("\\Images\\search.png"), wxBITMAP_TYPE_PNG);
	m_pSearch = new wxBitmapButton(this, static_cast<int>(AID::ID_SEARCH), m_searchBmp, wxDefaultPosition, wxDefaultSize);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
	
	m_pFoodName = new wxTextCtrl(this, static_cast<int>(AID::ID_CALORIE_TEXT), wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(0, &m_itemName));

	// Initialize spin controls
	m_pCalories = new wxSpinCtrl(this, static_cast<int>(AID::ID_CALORIE_SPIN), _T("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000);
	m_pCalories->SetValidator(wxGenericValidator(&m_calorieContent)); // wxSpinCtrl does not take a validator in the ctor, so set it here.

	m_pCarbCtrl = new wxSpinCtrl(this, static_cast<int>(AID::ID_CARB_SPIN), _T("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000);
	m_pCarbCtrl->SetValidator(wxGenericValidator(&m_carbContent));
	m_pCarbCtrl->Show(false);

	m_pProteinCtrl = new wxSpinCtrl(this, static_cast<int>(AID::ID_PROTEIN_SPIN), _T("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000);
	m_pProteinCtrl->SetValidator(wxGenericValidator(&m_proteinContent));
	m_pProteinCtrl->Show(false);

	m_pFiberCtrl = new wxSpinCtrl(this, static_cast<int>(AID::ID_FIBER_SPIN), _T("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000);
	m_pFiberCtrl->SetValidator(wxGenericValidator(&m_fiberContent));
	m_pFiberCtrl->Show(false);
}

void AddItemDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pItemSizer = new wxFlexGridSizer(3, wxSize(5, 1));
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	// initialize any static text/line objects
	itemName = new wxStaticText(this, wxID_STATIC, _T("Item name:"));
	calories = new wxStaticText(this, wxID_STATIC, _T("Calories:"));
	other = new wxStaticText(this, wxID_STATIC, _T("(Optional) Enter any other nutritional information about the item:")); other->Show(false);
	carbohydrates = new wxStaticText(this, wxID_STATIC, _T("Carbohydrates:")); carbohydrates->Show(false);
	protein = new wxStaticText(this, wxID_STATIC, _T("Protein:")); protein->Show(false);
	fiber = new wxStaticText(this, wxID_STATIC, _T("Fiber:")); fiber->Show(false);

	line1 = new wxStaticLine(this, wxID_STATIC); line1->Show(false);
	line2 = new wxStaticLine(this, wxID_STATIC);

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Proportion(0).Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Proportion(0).Border(wxALL, 5));

	m_pItemSizer->Add(itemName, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
	m_pItemSizer->Add(m_pFoodName, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
	m_pItemSizer->Add(m_pSearch, wxSizerFlags().Left().Border(wxALL, 5));

	m_pItemSizer->Add(calories, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
	m_pItemSizer->Add(m_pCalories, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
	m_pItemSizer->AddSpacer(5);

	m_pItemSizer->Add(m_pEnableMacros, wxSizerFlags().Left().Border(wxALL, 5));
	m_pItemSizer->AddSpacer(5);
	m_pTopSizer->Add(m_pItemSizer, wxSizerFlags().Left().Border(wxALL, 5));

	m_pTopSizer->Add(line1, wxSizerFlags().Proportion(0).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(other, wxSizerFlags().Left().Border(wxALL, 5));

	m_pItemSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pItemSizer->Add(carbohydrates, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
	m_pItemSizer->Add(m_pCarbCtrl, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));

	m_pItemSizer->Add(protein, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
	m_pItemSizer->Add(m_pProteinCtrl, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));

	m_pItemSizer->Add(fiber, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
	m_pItemSizer->Add(m_pFiberCtrl, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pItemSizer, wxSizerFlags().Left().Border(wxALL, 5));

	m_pTopSizer->Add(line2, wxSizerFlags().Proportion(0).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().Border(wxALL, 5));
}

void AddItemDlg::HandleExit()
{
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

void AddItemDlg::ShowControls(bool bShow)
{
	if (bShow)
	{
		carbohydrates->Show(true);
		m_pCarbCtrl->Show(true);

		protein->Show(true);
		m_pProteinCtrl->Show(true);

		fiber->Show(true);
		m_pFiberCtrl->Show(true);
	}
	else if (!bShow)
	{
		carbohydrates->Show(false);
		m_pCarbCtrl->Show(false);

		protein->Show(false);
		m_pProteinCtrl->Show(false);

		fiber->Show(false);
		m_pFiberCtrl->Show(false);
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

void AddItemDlg::OnUpdateControls(wxUpdateUIEvent& event)
{
	// The checkbox has been selected
	if (m_pEnableMacros->GetValue())
	{
		// show all items
		this->ShowControls(true);
		this->Layout();
	}
	else if (!m_pEnableMacros->GetValue())
	{
		this->ShowControls(false);
		this->Layout();
	}
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