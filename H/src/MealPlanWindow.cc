#include "MealPlanWindow.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(MealPlanWindow, wxFrame)

END_EVENT_TABLE()

MealPlanWindow::MealPlanWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	this->Init();
}

MealPlanWindow::~MealPlanWindow()
{
}

void MealPlanWindow::Init()
{
	this->SetupWindowIcon();
	this->SetupSizing();
}

void MealPlanWindow::SetupWindowIcon()
{
	m_mealIcon = wxIcon(path_data::dataDir + _T("\\Images\\meal_plan_small.png"), wxBITMAP_TYPE_PNG);
	this->SetIcon(m_mealIcon);
}

void MealPlanWindow::SetupSizing()
{

}