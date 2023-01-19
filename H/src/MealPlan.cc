#include <wx/statline.h>
#include "MealPlan.h"
#include "StandardPath.hpp"

// MealPlan panel event table
BEGIN_EVENT_TABLE(MealPlan, wxSplitterWindow)
	EVT_BUTTON(static_cast<int>(MP::ID_ADD_PLAN), MealPlan::OnAddMealPlan)
	EVT_BUTTON(static_cast<int>(MP::ID_CHANGE_FEATURED_LIST), MealPlan::OnChangeFeaturedPlan)
END_EVENT_TABLE()

// ================== MealPlan ==================

MealPlan::MealPlan(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxSplitterWindow(parent, id, pos, size, style)
{
	this->Init();
}

void MealPlan::Init()
{
	this->SetupPanels();
	this->SetupControls();
	this->SetupSizers();
	this->SetupSplitter();
}

void MealPlan::SetupSplitter()
{
	this->SetSashGravity(0.3);
	this->SetMinimumPaneSize(150);
	this->SetSashPosition(130);
}

void MealPlan::SetupPanels()
{
	m_pPlansPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pFeaturedPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	
	// Split the windows and set up properties
	this->SplitVertically(m_pPlansPanel, m_pFeaturedPanel);
}

void MealPlan::SetupControls()
{
	// Buttons
	m_addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_pAddMeal = new wxButton(m_pPlansPanel, static_cast<int>(MP::ID_ADD_PLAN), _T("Add Meal Plan"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pAddMeal->SetBitmap(m_addBmp);

	m_changeBmp = wxBitmap(path_data::dataDir + _T("\\Images\\change.png"), wxBITMAP_TYPE_PNG);
	m_pChangeFeatured = new wxButton(m_pFeaturedPanel, static_cast<int>(MP::ID_CHANGE_FEATURED_LIST), _T("Change Featured Plan"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pChangeFeatured->SetBitmap(m_changeBmp);

	// Lists
	m_pMealList = new MealList(m_pPlansPanel, static_cast<int>(MP::ID_MEAL_LIST), wxDefaultPosition, wxDefaultSize);
	m_pFeaturedList = new FeaturedList(m_pFeaturedPanel, static_cast<int>(MP::ID_FEATURED_LIST), wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
}

void MealPlan::SetupSizers()
{
	// Initialization
	m_pPlansSizer = new wxStaticBoxSizer(wxVERTICAL, m_pPlansPanel, _T("Meal Plans"));
	m_pFeaturedSizer = new wxStaticBoxSizer(wxVERTICAL, m_pFeaturedPanel, _T("Featured Plan"));

	m_pPlansPanel->SetSizerAndFit(m_pPlansSizer);
	m_pFeaturedPanel->SetSizerAndFit(m_pFeaturedSizer);

	// Add controls
	m_pPlansSizer->Add(m_pAddMeal, wxSizerFlags().Left().Border(wxALL, 5));
	m_pPlansSizer->Add(m_pMealList, wxSizerFlags().Proportion(1).Expand().Left().Border(wxALL, 5));
	m_pFeaturedSizer->Add(m_pChangeFeatured, wxSizerFlags().Left().Border(wxALL, 5));
	m_pFeaturedSizer->Add(m_pFeaturedList, wxSizerFlags().Proportion(1).Expand().Left().Border(wxALL, 5));
}

// events

void MealPlan::OnAddMealPlan(wxCommandEvent& event)
{
	m_pMealPlanWin = new MealPlanWindow(m_mealPlanInfoVec, m_pMealList, this, wxID_ANY, _T("Meal Planner"), wxDefaultPosition, wxDefaultSize);
	m_pMealPlanWin->Show(true);

	// Catch when the window is being destroyed to handle information
	m_pMealPlanWin->Bind(wxEVT_DESTROY, wxWindowDestroyEventHandler(MealPlan::OnCloseMealPlanWindow), this);
}

void MealPlan::OnChangeFeaturedPlan(wxCommandEvent& event)
{
	m_pChangeFeaturedPlanDlg = new ChangeFeaturedDialog(m_pMealList, this, wxID_ANY, _T("Change Featured Meal Plan"));
	m_pChangeFeaturedPlanDlg->Show(true);
}

void MealPlan::OnCloseMealPlanWindow(wxWindowDestroyEvent& event)
{
	
}

// ================== FeaturedList ==================

FeaturedList::FeaturedList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();
}

void FeaturedList::Init()
{
	this->SetupColumns();
}

void FeaturedList::SetupColumns()
{
	// Append days of week to a string array
	m_daysOfWeek.Add(_T("Sunday"));
	m_daysOfWeek.Add(_T("Monday"));
	m_daysOfWeek.Add(_T("Tuesday"));
	m_daysOfWeek.Add(_T("Wednesday"));
	m_daysOfWeek.Add(_T("Thursday"));
	m_daysOfWeek.Add(_T("Friday")); 
	m_daysOfWeek.Add(_T("Saturday"));

	// Loop through the strings add columns
	for (auto i{ 0 }; i < m_daysOfWeek.size(); ++i)
	{
		this->AppendColumn(m_daysOfWeek[i]);
	}
}

// ================== ChangeFeaturedDialog ==================

ChangeFeaturedDialog::ChangeFeaturedDialog(MealList* pMealList, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_pMealList{ pMealList }
{
	this->Init();
}

ChangeFeaturedDialog::~ChangeFeaturedDialog()
{
	// Unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &ChangeFeaturedDialog::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &ChangeFeaturedDialog::OnCancel, this, wxID_CANCEL);
	this->Unbind(wxEVT_CLOSE_WINDOW, &ChangeFeaturedDialog::OnClose, this, wxID_CLOSE);
}

void ChangeFeaturedDialog::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void ChangeFeaturedDialog::SetupControls()
{
	// Add all the item names to a wxArrayString
	for (auto i{ 0 }; i < m_pMealList->GetItemCount(); ++i)
	{
		m_mealStrings.Add(m_pMealList->GetItemText(i));
	}

	m_pMealChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_mealStrings);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);	
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);

	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &ChangeFeaturedDialog::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &ChangeFeaturedDialog::OnCancel, this, wxID_CANCEL);
	this->Bind(wxEVT_CLOSE_WINDOW, &ChangeFeaturedDialog::OnClose, this, wxID_CLOSE);
}

void ChangeFeaturedDialog::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pHorizontalSizer = new wxFlexGridSizer(2, wxSize(5, 1)); // Re-init this sizer for main controls & buttons
	this->SetSizerAndFit(m_pTopSizer);

	m_pHorizontalSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Featured plan:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pMealChoice, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pHorizontalSizer, wxSizerFlags().CentreHorizontal());

	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));

	// Buttons
	m_pHorizontalSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pHorizontalSizer->Add(m_pOk, wxSizerFlags().Left().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pCancel, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pHorizontalSizer, wxSizerFlags().CentreHorizontal());
}

void ChangeFeaturedDialog::SetupSizing()
{
	this->SetMinSize(CFD_SIZE);
	this->SetInitialSize(CFD_SIZE);
	this->SetMaxSize(CFD_MAX_SIZE);
}

// events

void ChangeFeaturedDialog::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void ChangeFeaturedDialog::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

void ChangeFeaturedDialog::OnClose(wxCloseEvent& event)
{
	this->Destroy();
}