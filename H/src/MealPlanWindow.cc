#include <wx/valgen.h>
#include <wx/valtext.h>
#include <wx/stattext.h>
#include <wx/statline.h>
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
	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);
	m_pTopPanel->SetSizerAndFit(m_pMainSizer);

	m_pTopSizer->Add(m_pTopPanel, wxSizerFlags().Proportion(1).Expand());
	m_pMainSizer->Add(m_pAddMeal, wxSizerFlags().Left().Border(wxALL, 5));
}

void MealPlanWindow::SetupLists()
{

}

// events

void MealPlanWindow::OnAddMeal(wxCommandEvent& event)
{
	m_pAddMealDlg = new AddMealDialog(this, wxID_ANY);
	m_pAddMealDlg->Show(true);
}

// ========================== AddMealDialog ==========================

AddMealDialog::AddMealDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();

	// Connect events
	m_pOk->Bind(wxEVT_BUTTON, &AddMealDialog::OnOK, this);
	m_pOk->Bind(wxEVT_UPDATE_UI, &AddMealDialog::OnUpdateOK, this);
	m_pCancel->Bind(wxEVT_BUTTON, &AddMealDialog::OnCancel, this);
}

AddMealDialog::~AddMealDialog()
{
	m_pOk->Unbind(wxEVT_BUTTON, &AddMealDialog::OnOK, this);
	m_pOk->Unbind(wxEVT_UPDATE_UI, &AddMealDialog::OnUpdateOK, this);
	m_pCancel->Unbind(wxEVT_BUTTON, &AddMealDialog::OnCancel, this);
}

void AddMealDialog::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void AddMealDialog::SetupSizing()
{
	this->SetInitialSize(AMD_SIZE);
	this->SetMinSize(AMD_SIZE);
	this->SetMaxSize(AMD_MAX_SIZE);
}

void AddMealDialog::SetupControls()
{
	// Text fields
	m_pMealNameTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxTextValidator(0, &m_mealName));
	m_pMealDescTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE, wxTextValidator(0, &m_mealDesc));

	// Buttons
	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pOk->Enable(false); // At first, we want the OK button disabled. It will get re-enable dwhen the user has entered a day of the week and entered a meal name

	// Day-of-week selection
	m_choiceArr.Add(_T("Sunday"));
	m_choiceArr.Add(_T("Monday"));
	m_choiceArr.Add(_T("Tuesday"));
	m_choiceArr.Add(_T("Wednesday"));
	m_choiceArr.Add(_T("Thursday"));
	m_choiceArr.Add(_T("Friday"));
	m_choiceArr.Add(_T("Saturday"));
	m_pDayChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceArr, 0, wxGenericValidator(&m_choiceValue));
}

void AddMealDialog::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pFlexSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);
	
	// Add controls to the flex sizer
	m_pFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Meal Name:")), wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pFlexSizer->Add(m_pMealNameTxt, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));

	m_pFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("(Optional) Meal Description:")), wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pFlexSizer->Add(m_pMealDescTxt, wxSizerFlags().CentreVertical().Proportion(1).Expand().Border(wxALL, 5));

	m_pFlexSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Day of Week:")), wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pFlexSizer->Add(m_pDayChoice, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));

	// Button sizer
	m_pButtonSizer->Add(m_pOk, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().CentreVertical().Border(wxALL, 5));

	// Arrange the elements
	m_pTopSizer->Add(m_pFlexSizer, wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().Border(wxALL, 5));
}

void AddMealDialog::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		if (IsModal())
			EndModal(wxID_OK);
		else
		{
#ifdef _DEBUG
			wxLogMessage(_T("%s\n%s\n%s"), m_mealName, m_mealDesc, m_pDayChoice->GetStringSelection());
#endif
			SetReturnCode(wxID_OK);
			Show(false);
		}
	}
}

void AddMealDialog::OnCancel(wxCommandEvent& event)
{
	this->Destroy();
}

void AddMealDialog::OnUpdateOK(wxUpdateUIEvent& event)
{
	if (!m_pMealNameTxt->IsEmpty() && m_pDayChoice->GetSelection() != -1)
		event.Enable(true);
	else
		event.Enable(false);
}

// ========================== MealDayList ==========================

MealDayList::MealDayList(const wxString& list_title, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView{ parent, id, pos, size, style }, m_listTitle{ list_title }
{

}
