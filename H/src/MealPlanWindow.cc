#include <wx/valgen.h>
#include <wx/valtext.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/msgdlg.h>
#include "MealPlanWindow.h"
#include "StandardPath.hpp"

MealPlanWindow::MealPlanWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style, _T("mealplanwin"))
{
	this->Init();
	this->Centre();

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
	this->SetupLists();
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

	m_saveBmp = wxBitmap(path_data::dataDir + _T("\\Images\\save.png"), wxBITMAP_TYPE_PNG);
	m_pSavePlan = new wxButton(m_pTopPanel, static_cast<int>(MPW::ID_SAVE_PLAN), _T("Save Plan"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pSavePlan->SetBitmap(m_saveBmp);
}

void MealPlanWindow::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pDaySizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);
	m_pTopPanel->SetSizerAndFit(m_pMainSizer);

	// Button sizer
	m_pButtonSizer->Add(m_pAddMeal, wxSizerFlags().Left().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pSavePlan, wxSizerFlags().Left().Border(wxALL, 5));

	// Add day of week lists to the sizer
	for (auto i{ 0 }; i < m_pDayList.size(); ++i)
	{
		m_pDaySizer->Add(m_pDayList[i], wxSizerFlags().Proportion(1).Expand().Border(wxALL, 1));
	}

	m_pTopSizer->Add(m_pTopPanel, wxSizerFlags().Proportion(1).Expand());
	m_pMainSizer->Add(m_pButtonSizer, wxSizerFlags().Left().Border(wxALL, 5));
	m_pMainSizer->Add(m_pDaySizer, wxSizerFlags().Left().Proportion(1).Expand().Border(wxALL, 5));
}

void MealPlanWindow::SetupLists()
{
	m_pDayList.push_back(new MealDayList(_T("Sunday"), m_pTopPanel, wxID_ANY));
	m_pDayList.push_back(new MealDayList(_T("Monday"), m_pTopPanel, wxID_ANY));
	m_pDayList.push_back(new MealDayList(_T("Tuesday"), m_pTopPanel, wxID_ANY));
	m_pDayList.push_back(new MealDayList(_T("Wednesday"), m_pTopPanel, wxID_ANY));
	m_pDayList.push_back(new MealDayList(_T("Thursday"), m_pTopPanel, wxID_ANY));
	m_pDayList.push_back(new MealDayList(_T("Friday"), m_pTopPanel, wxID_ANY));
	m_pDayList.push_back(new MealDayList(_T("Saturday"), m_pTopPanel, wxID_ANY));
}

// events

void MealPlanWindow::OnAddMeal(wxCommandEvent& event)
{
	m_pAddMealDlg = new AddMealDialog(this, wxID_ANY);
	m_pAddMealDlg->Show(true);

	if (m_pAddMealDlg->ShowModal() == wxID_OK)
	{
		// Add the item to the corresponding list
		// Loop through the lists to check which day of the week the user chose
		for (auto i{ 0 }; i < m_pDayList.size(); ++i)
		{
			if (m_pDayList[i]->GetListTitle() == m_pAddMealDlg->GetChoiceStr())
				m_pDayList[i]->AddItem(m_pAddMealDlg->GetMealName());

			// Push back the item onto the information array
		}
	}
}



// ========================== SaveMealPlanDialog ==========================

SaveMealPlanDialog::SaveMealPlanDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
}

SaveMealPlanDialog::~SaveMealPlanDialog()
{
}

void SaveMealPlanDialog::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void SaveMealPlanDialog::SetupControls()
{

}

void SaveMealPlanDialog::SetupSizers()
{

}

void SaveMealPlanDialog::OnOK(wxCommandEvent& event)
{
}

void SaveMealPlanDialog::OnCancel(wxCommandEvent& event)
{
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
	// Unbind events
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
	this->Init();

	// Bind events
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MealDayList::OnRightClickItem, this);
	this->Bind(wxEVT_LIST_COL_RIGHT_CLICK, &MealDayList::OnRightClickColumn, this);//
	m_pMenu->Bind(wxEVT_MENU, &MealDayList::OnDeleteItem, this, wxID_DELETE);
	m_pMenu->Bind(wxEVT_MENU, &MealDayList::OnViewItem, this, wxID_VIEW_DETAILS);
	m_pColMenu->Bind(wxEVT_MENU, &MealDayList::OnResetList, this, wxID_RESET);
}

MealDayList::~MealDayList()
{
	// Unbind events
	this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MealDayList::OnRightClickItem, this);
	this->Unbind(wxEVT_LIST_COL_RIGHT_CLICK, &MealDayList::OnRightClickColumn, this);
	m_pMenu->Unbind(wxEVT_MENU, &MealDayList::OnDeleteItem, this, wxID_DELETE);
	m_pMenu->Unbind(wxEVT_MENU, &MealDayList::OnViewItem, this, wxID_VIEW_DETAILS);
	m_pColMenu->Unbind(wxEVT_MENU, &MealDayList::OnResetList, this, wxID_RESET);
}

void MealDayList::Init()
{
	this->SetupColumn();
	this->SetupMenu();
	this->SetupImageList();
}

void MealDayList::SetupColumn()
{
	wxListItem col;
	col.SetText(m_listTitle);
	col.SetImage(-1);
	this->InsertColumn(0, col);
	//this->SetColumnWidth(0, ...)
}

void MealDayList::SetupMenu()
{
	// Menu for when individual items are right-clicked
	m_pMenu = new wxMenu();
	m_pMenu->Append(wxID_VIEW_DETAILS, _T("&View"));
	m_pMenu->AppendSeparator();
	m_pMenu->Append(wxID_DELETE, _T("&Delete"));

	// Menu for when the column title is right-clicked
	m_pColMenu = new wxMenu();
	m_pColMenu->Append(wxID_RESET, _T("&Reset List"));
}

void MealDayList::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_mealBmp = wxBitmap(path_data::dataDir + _T("\\Images\\meal_plan_small.png"), wxBITMAP_TYPE_PNG);
	m_mealBmp.ResetAlpha();

	m_pImageList->Add(m_mealBmp);
	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void MealDayList::ResetList()
{
	this->DeleteAllItems();
}

void MealDayList::AddItem(const wxString& name)
{
	this->InsertItem(0, name, 0);
}

void MealDayList::OnRightClickItem(wxListEvent& event)
{
	// Display a pop-up menu for the meals when the user right clicks
	this->PopupMenu(m_pMenu);
}

void MealDayList::OnRightClickColumn(wxListEvent& event)
{
	this->PopupMenu(m_pColMenu);
}

void MealDayList::OnDeleteItem(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		this->DeleteItem(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
}

void MealDayList::OnViewItem(wxCommandEvent& event)
{
}

void MealDayList::OnResetList(wxCommandEvent& event)
{
	this->ResetList();
}