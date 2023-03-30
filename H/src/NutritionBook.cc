#include "NutritionBook.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(NutritionBook, wxNotebook)

END_EVENT_TABLE()

NutritionBook::NutritionBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxNotebook(parent, id, pos, size, style)
{
	this->Init();
}

NutritionBook::~NutritionBook()
{
}

void NutritionBook::Init()
{
	this->SetupImageList();
	this->SetupCaloriePanel();
	//this->SetupMealPlan();
	this->SetupPages();
}

void NutritionBook::SetupImageList()
{
	m_pImageList = new wxImageList(30, 30);

	m_calorieBmp = wxBitmap(path_data::dataDir + _T("\\Images\\calorie.png"), wxBITMAP_TYPE_PNG);
	m_calorieBmp.ResetAlpha();

	m_mealBmp = wxBitmap(path_data::dataDir + _T("\\Images\\meal_plan.png"), wxBITMAP_TYPE_PNG);
	m_mealBmp.ResetAlpha();

	m_pImageList->Add(m_calorieBmp);
	m_pImageList->Add(m_mealBmp);
	this->AssignImageList(m_pImageList);
}

void NutritionBook::SetupCaloriePanel()
{
	m_pCaloriePanel = new CaloriePanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pCaloriePanel->Show(true);
}

void NutritionBook::SetupMealPlan()
{
	m_pMealPlan = new MealPlan(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pMealPlan->Show(true);
}

void NutritionBook::SetupPages()
{
	this->AddPage(m_pCaloriePanel, _T("Nutrient Tracker"), true, 0);
}