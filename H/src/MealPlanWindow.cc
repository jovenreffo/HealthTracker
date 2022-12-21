#include "MealPlanWindow.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(MealPlanWindow, wxFrame)
	EVT_BUTTON(static_cast<int>(MPW::ID_ADD_MEAL), MealPlanWindow::OnAddMeal)
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
	this->SetupControls();
}

void MealPlanWindow::SetupWindowIcon()
{
	m_mealIcon = wxIcon(path_data::dataDir + _T("\\Images\\meal_plan_small.png"), wxBITMAP_TYPE_PNG);
	this->SetIcon(m_mealIcon);
}

void MealPlanWindow::SetupSizing()
{
	this->SetMinSize(MPW_SIZE);
	this->SetInitialSize(MPW_SIZE);
}

void MealPlanWindow::SetupControls()
{
	m_addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_pAddMeal = new wxButton(this, static_cast<int>(MPW::ID_ADD_MEAL), _T("Add Meal"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pAddMeal->SetBitmap(m_addBmp);
}

// events

void MealPlanWindow::OnAddMeal(wxCommandEvent& event)
{

}

// ========================== AddMealDialog ==========================
BEGIN_EVENT_TABLE(AddMealDialog, wxDialog)

END_EVENT_TABLE()

AddMealDialog::AddMealDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{

}

AddMealDialog::~AddMealDialog()
{

}
