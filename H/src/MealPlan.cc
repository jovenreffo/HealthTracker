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
	m_pAddMeal = new wxButton(this, static_cast<int>(MP::ID_ADD_PLAN), _T("Add Task"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pAddMeal->SetBitmap(m_addBmp);

	// Lists
	m_pMealList = new MealList(this, static_cast<int>(MP::ID_MEAL_LIST), wxDefaultPosition, wxDefaultSize);
	m_pFeaturedList = new wxListView(this, static_cast<int>(MP::ID_FEATURED_LIST), wxDefaultPosition, wxDefaultSize);

	// Sizers
}

void MealPlan::SetupSizers()
{
}

// ================== MealList ==================

MealList::MealList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
}
