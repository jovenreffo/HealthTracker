#include "MealPlan.h"
#include "StandardPath.hpp"

// MealPlan panel event table
BEGIN_EVENT_TABLE(MealPlan, wxSplitterWindow)


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
	this->SetMinimumPaneSize(100);
}

void MealPlan::SetupControls()
{
	// Button
	m_addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_pAddMeal = new wxButton(m_pPlansPanel, static_cast<int>(MP::ID_ADD_PLAN), _T("Add Meal"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pAddMeal->SetBitmap(m_addBmp);

	// Lists
	m_pMealList = new MealList(m_pPlansPanel, static_cast<int>(MP::ID_MEAL_LIST), wxDefaultPosition, wxDefaultSize);
	m_pFeaturedList = new wxListView(m_pFeaturedPanel, static_cast<int>(MP::ID_FEATURED_LIST), wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
}

void MealPlan::SetupSizers()
{
	wxBoxSizer* pPlansSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* pFeaturedSizer = new wxBoxSizer(wxVERTICAL);
	m_pPlansPanel->SetSizerAndFit(pPlansSizer);
	m_pFeaturedPanel->SetSizerAndFit(pFeaturedSizer);

	// Add controls

}

// ================== MealList ==================

MealList::MealList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
}
