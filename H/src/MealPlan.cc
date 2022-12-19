#include "MealPlan.h"
#include "StandardPath.hpp"

// MealPlan panel event table
BEGIN_EVENT_TABLE(MealPlan, wxPanel)


END_EVENT_TABLE()

// MealList evt table
BEGIN_EVENT_TABLE(MealList, wxListView)

END_EVENT_TABLE()

// ================== MealPlan ==================

MealPlan::MealPlan(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void MealPlan::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void MealPlan::SetupControls()
{
	// Button
	m_addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_pAddMeal = new wxButton(this, static_cast<int>(MP::ID_ADD_PLAN), _T("Add Meal"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pAddMeal->SetBitmap(m_addBmp);

	// Lists
	m_pMealList = new MealList(this, static_cast<int>(MP::ID_MEAL_LIST), wxDefaultPosition, wxDefaultSize);
	m_pFeaturedList = new wxListView(this, static_cast<int>(MP::ID_FEATURED_LIST), wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
}

void MealPlan::SetupSizers()
{
	// Initialization
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pListSizer = new wxBoxSizer(wxHORIZONTAL); // Horizontal sizer to arrange the 2 statbox sizers side by side
	m_pPlansList = new wxStaticBoxSizer(wxVERTICAL, this, _T("Meal Plans"));
	m_pFeaturedPlan = new wxStaticBoxSizer(wxVERTICAL, this, _T("Featured Plan"));
	this->SetSizerAndFit(m_pTopSizer);

	// Add items to the sizers
	m_pTopSizer->Add(m_pAddMeal, wxSizerFlags().Left().Border(wxALL, 5));
	m_pPlansList->Add(m_pMealList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pFeaturedPlan->Add(m_pFeaturedList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pListSizer->Add(m_pPlansList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pListSizer->Add(m_pFeaturedPlan, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));

	// Add sizers to the top-level
	m_pTopSizer->Add(m_pListSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

void MealPlan::SetupPanels()
{

}

void MealPlan::SetupSplitter()
{

}

// ================== MealList ==================

MealList::MealList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
}
