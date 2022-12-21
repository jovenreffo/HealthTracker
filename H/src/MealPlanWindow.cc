#include "MealPlanWindow.h"
#include "StandardPath.hpp"

MealPlanWindow::MealPlanWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style, _T("mealplanwin"))
{
	this->Init();

	// Bind events
	m_pAddMeal->Bind(wxEVT_BUTTON, &MealPlanWindow::OnAddMeal, this);
}

MealPlanWindow::~MealPlanWindow()
{
	// Unbind evnets
	m_pAddMeal->Unbind(wxEVT_BUTTON, &MealPlanWindow::OnAddMeal, this);
}

void MealPlanWindow::Init()
{
	m_pTopPanel = new wxPanel(this);
	this->SetupWindowIcon();
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
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
	m_pAddMeal = new wxButton(m_pTopPanel, static_cast<int>(MPW::ID_ADD_MEAL), _T("Add Meal"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pAddMeal->SetBitmap(m_addBmp);
}

void MealPlanWindow::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pMainSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);
	m_pTopPanel->SetSizerAndFit(m_pMainSizer);

	m_pTopSizer->Add(m_pTopPanel, wxSizerFlags().Proportion(1).Expand());
	m_pMainSizer->Add(m_pAddMeal, wxSizerFlags().Left().Border(wxALL, 5));
}

// events

void MealPlanWindow::OnAddMeal(wxCommandEvent& event)
{

}

// ========================== AddMealDialog ==========================

AddMealDialog::AddMealDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{

}

AddMealDialog::~AddMealDialog()
{

}
