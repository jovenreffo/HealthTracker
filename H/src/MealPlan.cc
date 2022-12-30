#include "MealPlan.h"
#include "StandardPath.hpp"

// MealPlan panel event table
BEGIN_EVENT_TABLE(MealPlan, wxSplitterWindow)
	EVT_BUTTON(static_cast<int>(MP::ID_ADD_PLAN), MealPlan::OnAddMealPlan)
END_EVENT_TABLE()

// MealList evt table
BEGIN_EVENT_TABLE(MealList, wxListView)

END_EVENT_TABLE()

// ================== MealPlan ==================

MealPlan::MealPlan(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxSplitterWindow(parent, id, pos, size, style)
{
	this->Init();
}

void MealPlan::Init()
{
	this->SetupSplitter();
	this->SetupPanels();
	this->SetupControls();
	this->SetupSizers();
}

void MealPlan::SetupSplitter()
{
	this->SetSashGravity(0.5);
	this->SetMinimumPaneSize(100);
}

void MealPlan::SetupPanels()
{
	m_pPlansPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pFeaturedPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	
	// Split the windows and set up properties
	this->SplitVertically(m_pPlansPanel, m_pFeaturedPanel);
	this->SetSashGravity(0.5);
	this->SetMinimumPaneSize(200);
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
	m_pFeaturedList = new wxListView(m_pFeaturedPanel, static_cast<int>(MP::ID_FEATURED_LIST), wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
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
	m_pMealPlanWin = new MealPlanWindow(m_pMealList, this, wxID_ANY, _T("Meal Planner"), wxDefaultPosition, wxDefaultSize);
	m_pMealPlanWin->Show(true);
}