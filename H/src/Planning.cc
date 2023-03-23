#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/valtext.h>
#include <wx/msgdlg.h>

#include "Planning.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"
#include "Flags.hpp"

Planning::Planning(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxNotebook(parent, id, pos, size, style, _T("calendar"))
{
	this->Init();
}

void Planning::Init()
{
	this->SetupImageList();
	this->SetupPages();
}

void Planning::SetupImageList()
{
	m_pImageList = new wxImageList(30, 30);

	m_calendarBmp = wxBitmap(path_data::dataDir + _T("\\Images\\calendar_small.png"), wxBITMAP_TYPE_PNG);
	m_calendarBmp.ResetAlpha();

	m_todoBmp = wxBitmap(path_data::dataDir + _T("\\Images\\tasklist.png"), wxBITMAP_TYPE_PNG);
	m_todoBmp.ResetAlpha();

	m_pImageList->Add(m_calendarBmp);
	m_pImageList->Add(m_todoBmp);
	this->AssignImageList(m_pImageList);
}

void Planning::SetupPages()
{
	m_pCalendarPanel = new CalendarPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pTodoPanel = new TodoPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// Set up pages in the notebook
	this->AddPage(m_pCalendarPanel, _T("Calendar"), true, 0);
	this->AddPage(m_pTodoPanel, _T("To-Do List"), false, 1);
}

// =========================================== CalendarPanel ===========================================

CalendarPanel::CalendarPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style, _T("caloriepanel"))
{
}

// =========================================== AddTaskDlg ===========================================

AddTaskDlg::AddTaskDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();

	// Bind events
	m_pTaskNameTxt->Bind(wxEVT_TEXT_ENTER, &AddTaskDlg::OnTextEnter, this);
	m_pTaskDescTxt->Bind(wxEVT_TEXT_ENTER, &AddTaskDlg::OnTextEnter, this);
	m_pOk->Bind(wxEVT_BUTTON, &AddTaskDlg::OnOK, this);
	m_pCancel->Bind(wxEVT_BUTTON, &AddTaskDlg::OnCancel, this);

	m_pTaskNameTxt->Bind(wxEVT_TEXT_MAXLEN, &AddTaskDlg::OnMaxLengthName, this);
	m_pTaskDescTxt->Bind(wxEVT_TEXT_MAXLEN, &AddTaskDlg::OnMaxLengthDesc, this);
}

AddTaskDlg::~AddTaskDlg()
{
	// Unbind events
	m_pTaskNameTxt->Unbind(wxEVT_TEXT_ENTER, &AddTaskDlg::OnTextEnter, this);
	m_pTaskDescTxt->Unbind(wxEVT_TEXT_ENTER, &AddTaskDlg::OnTextEnter, this);
	m_pOk->Unbind(wxEVT_BUTTON, &AddTaskDlg::OnOK, this);
	m_pCancel->Unbind(wxEVT_BUTTON, &AddTaskDlg::OnCancel, this);

	m_pTaskNameTxt->Unbind(wxEVT_TEXT_MAXLEN, &AddTaskDlg::OnMaxLengthName, this);
	m_pTaskDescTxt->Unbind(wxEVT_TEXT_MAXLEN, &AddTaskDlg::OnMaxLengthDesc, this);
}

void AddTaskDlg::Init()
{
	this->SetupPriorityLevels();
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void AddTaskDlg::SetupPriorityLevels()
{
	m_priorityLevels.Add(_T("Minor"));
	m_priorityLevels.Add(_T("Medium"));
	m_priorityLevels.Add(_T("Major"));
}

void AddTaskDlg::SetupControls()
{
	m_pTaskNameTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxTextValidator(0, &m_taskName));
	m_pTaskDescTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER, wxTextValidator(0, &m_taskDesc));

	// Set max lengths
	m_pTaskNameTxt->SetMaxLength(35);
	m_pTaskDescTxt->SetMaxLength(100);

	m_pPriorityLevel = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_priorityLevels);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
}

void AddTaskDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pTextSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	this->SetSizerAndFit(m_pTopSizer);

	// Main text controls
	m_pTextSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Task title:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pTextSizer->Add(m_pTaskNameTxt, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTextSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Task description:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pTextSizer->Add(m_pTaskDescTxt, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTextSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Priority level:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pTextSizer->Add(m_pPriorityLevel, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pTextSizer, wxSizerFlags().Left().Border(wxALL, 5));

	// Separator
	m_pTopSizer->Add(new wxStaticLine(this), wxSizerFlags().Expand().Border(wxALL, 5));

	// Buttons
	m_pButtonSizer->Add(m_pOk, SIZER_FLAGS_LEFT);
	m_pButtonSizer->Add(m_pCancel, SIZER_FLAGS_LEFT);
	m_pTopSizer->Add(m_pButtonSizer, SIZER_FLAGS_LEFT);
}

void AddTaskDlg::SetupSizing()
{
	this->SetInitialSize(ADDTASKDLG_SIZE);
	this->SetMinSize(ADDTASKDLG_SIZE);
	this->SetMaxSize(ADDTASKDLG_MAX_SIZE);
}

void AddTaskDlg::HandleExit()
{
	if (Validate() && TransferDataFromWindow())
	{
		if (IsModal())
			EndModal(wxID_OK);
		else
		{
			SetReturnCode(wxID_OK);
			Show(false);
		}
	}
}

// events

void AddTaskDlg::OnTextEnter(wxCommandEvent& e)
{
	this->HandleExit();
}

void AddTaskDlg::OnOK(wxCommandEvent& e)
{
	this->HandleExit();
}

void AddTaskDlg::OnCancel(wxCommandEvent& e)
{
	SetReturnCode(wxID_CANCEL);
	Show(false);
}

void AddTaskDlg::OnMaxLengthName(wxCommandEvent& e)
{
	wxMessageBox(_T("You have reached the character limit (75/75)"), _T("Warning"), wxOK | wxICON_EXCLAMATION);
	e.Skip();
}

void AddTaskDlg::OnMaxLengthDesc(wxCommandEvent& e)
{
	wxMessageBox(_T("You have reached the character limit (200/200)"), _T("Warning"), wxOK | wxICON_EXCLAMATION);
	e.Skip();
}

// =========================================== TodoPanel ===========================================

TodoPanel::TodoPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxScrolled<wxPanel>(parent, id, pos, size, style, _T("todopanel"))
{
	this->Init();

	// Bind events
	m_pAddButton->Bind(wxEVT_BUTTON, &TodoPanel::OnAddTask, this);
	m_pClearListButton->Bind(wxEVT_BUTTON, &TodoPanel::OnClearTaskList, this);
}

TodoPanel::~TodoPanel()
{
	// Unbind events
	m_pAddButton->Unbind(wxEVT_BUTTON, &TodoPanel::OnAddTask, this);
	m_pClearListButton->Unbind(wxEVT_BUTTON, &TodoPanel::OnClearTaskList, this);
}

// Panel setup
void TodoPanel::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupPanels(); // SetupSplitter() called here
}

void TodoPanel::SetupControls()
{
	m_addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_checkBmp = wxBitmap(path_data::dataDir + _T("\\Images\\check2.png"), wxBITMAP_TYPE_PNG);

	m_pAddButton = new wxButton(this, wxID_ANY, _T("Add Task"), wxDefaultPosition, wxDefaultSize);
	m_pClearListButton = new wxButton(this, wxID_ANY, _T("Clear Task List"), wxDefaultPosition, wxDefaultSize);

	m_pAddButton->SetBitmap(m_addBmp);
	m_pClearListButton->SetBitmap(m_checkBmp);
}

void TodoPanel::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pTopButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopButtonSizer->Add(m_pAddButton, SIZER_FLAGS_LEFT);
	m_pTopButtonSizer->Add(m_pClearListButton, SIZER_FLAGS_LEFT);
	m_pTopSizer->Add(m_pTopButtonSizer);
#ifdef wxUSE_STATLINE
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
#endif
}

void TodoPanel::SetupPanels()
{
	this->SetupSplitter();

	m_pCompletedPanel = new wxPanel(m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pTaskPanel = new wxPanel(m_pSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// initialise the task list with m_pCompletedPanel as the parent
	m_pTaskList = new TaskList(m_pCompletedPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// sizers
	m_pCompletedSizer = new wxBoxSizer(wxVERTICAL);
	m_pTaskSizer = new wxBoxSizer(wxVERTICAL);
	m_pCompletedPanel->SetSizerAndFit(m_pCompletedSizer);
	m_pTaskPanel->SetSizerAndFit(m_pTaskSizer);

	// static box sizer for completed task panel
	m_pListSizer = new wxStaticBoxSizer(wxVERTICAL, m_pCompletedPanel, _T("Completed Tasks"));
	m_pListSizer->Add(m_pTaskList, wxSizerFlags().Expand().Proportion(1).Border(wxALL, 5));
	m_pCompletedSizer->Add(m_pListSizer, wxSizerFlags().Expand().Proportion(1).Border(wxALL, 5));

	// Split
	m_pSplitter->SplitVertically(m_pTaskPanel, m_pCompletedPanel);
	m_pTopSizer->Add(m_pSplitter, wxSizerFlags().Expand().Proportion(1).Border(wxALL, 5));
}

void TodoPanel::SetupSplitter()
{
	m_pSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH | wxSP_LIVE_UPDATE | wxSP_NOBORDER);
	m_pSplitter->SetSashGravity(0.5);
	m_pSplitter->SetMinimumPaneSize(150);
}

void TodoPanel::AddTask(int priorityLevel, const wxString& name, const wxString& desc)
{
	// Create a new item and push it back into the vector
	TodoItem* pItem = new TodoItem(priorityLevel, name, desc, m_pTaskList, m_pTaskPanel);
	pItem->Show(true);
	m_items.push_back(pItem);

	// Layout the window
	m_pTaskSizer->Add(pItem, wxSizerFlags().Expand().Proportion(1).Border(wxALL, 5));
	m_pTaskPanel->Layout();
}

// Events

void TodoPanel::OnAddTask(wxCommandEvent& e)
{
	m_pAddTaskDlg = new AddTaskDlg(this);
	m_pAddTaskDlg->Show(true);

	if (m_pAddTaskDlg->ShowModal() == wxID_OK)
	{
		this->AddTask(m_pAddTaskDlg->GetPriorityLevel(), m_pAddTaskDlg->GetTaskName(), m_pAddTaskDlg->GetTaskDesc());
	}
}

void TodoPanel::OnClearTaskList(wxCommandEvent& e)
{
	if (wxMessageBox(_T("Are you sure you want to remove all of your tasks?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
	{
		wxLogMessage("Active items: %d", m_items.size());
		for (auto i : m_items)
		{
			i->Show(false);
			i->Destroy();
			this->Layout();
		}
	}
}

// =========================================== TodoItem ===========================================

TodoItem::TodoItem(int priorityLevel, const wxString& taskName, const wxString& taskDesc, TaskList* pTaskList, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxPanel(parent, id, pos, size, style), m_nPriorityLevel{ priorityLevel }, m_taskName{ taskName }, m_taskDesc{ taskDesc }, m_pTaskList{ pTaskList }
{
	this->Init();
	this->SetBackgroundColour(wxColour(225, 225, 225));

	// Bind events
	this->Bind(wxEVT_RIGHT_DOWN, &TodoItem::OnRightClick, this);
	this->Bind(wxEVT_PAINT, &TodoItem::OnPaint, this);

	// Menu events
	m_pMenu->Bind(wxEVT_MENU, &TodoItem::OnRemove, this, wxID_REMOVE);

	// Button events
	m_pMarkCompleted->Bind(wxEVT_BUTTON, &TodoItem::OnMarkCompleted, this);
}

TodoItem::~TodoItem()
{
	// Unbind events
	this->Unbind(wxEVT_RIGHT_DOWN, &TodoItem::OnRightClick, this);
	this->Unbind(wxEVT_PAINT, &TodoItem::OnPaint, this);
	m_pMarkCompleted->Unbind(wxEVT_CHECKBOX, &TodoItem::OnMarkCompleted, this);

	// Menu events
	m_pMenu->Unbind(wxEVT_MENU, &TodoItem::OnRemove, this, wxID_REMOVE);

	// Button events
	m_pMarkCompleted->Unbind(wxEVT_BUTTON, &TodoItem::OnMarkCompleted, this);
}

void TodoItem::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupPopupMenu();
}

void TodoItem::SetupControls()
{

	// buttons
	m_editBmp = wxBitmap(path_data::dataDir + _T("\\Images\\edit.png"), wxBITMAP_TYPE_PNG);
	m_removeBmp = wxBitmap(path_data::dataDir + _T("\\Images\\remove.png"), wxBITMAP_TYPE_PNG);
	m_checkBmp = wxBitmap(path_data::dataDir + _T("\\Images\\check2.png"), wxBITMAP_TYPE_PNG);
	m_pEditButton = new wxBitmapButton(this, wxID_ANY, m_editBmp, wxDefaultPosition, wxDefaultSize);
	m_pRemoveButton = new wxBitmapButton(this, wxID_ANY, m_removeBmp, wxDefaultPosition, wxDefaultSize);
	m_pMarkCompleted = new wxBitmapButton(this, wxID_ANY, m_checkBmp, wxDefaultPosition, wxDefaultSize);
	// tooltips
	m_pEditButton->SetToolTip(_T("Edit this task."));
	m_pRemoveButton->SetToolTip(_T("Remove this task."));
	m_pMarkCompleted->SetToolTip(_T("Mark this task as complete."));

	// initialise text objects
	m_pNameTitle = new wxStaticText(this, wxID_ANY, _T("Name"), wxDefaultPosition, wxDefaultSize);
	m_pDescTitle = new wxStaticText(this, wxID_ANY, _T("Description"), wxDefaultPosition, wxDefaultSize);
	// make the titles bold
	m_pNameTitle->SetFont(Fonts::GetBoldFont(10));
	m_pDescTitle->SetFont(Fonts::GetBoldFont(10));

	m_pItemName = new wxStaticText(this, wxID_ANY, m_taskName, wxDefaultPosition, wxDefaultSize);
	m_pItemDesc = new wxStaticText(this, wxID_ANY, m_taskDesc, wxDefaultPosition, wxDefaultSize);
}

void TodoItem::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pFlexSizer = new wxFlexGridSizer(2, wxSize(65, -1));
	m_pSettingsSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	// Settings sizer
	m_pSettingsSizer->Add(m_pMarkCompleted, wxSizerFlags().Left().Border(wxALL, 5));
	m_pSettingsSizer->Add(m_pEditButton, wxSizerFlags().Left().Border(wxALL, 5));
	m_pSettingsSizer->Add(m_pRemoveButton, wxSizerFlags().Left().Border(wxALL, 5));

	// Flex sizer
	m_pFlexSizer->Add(m_pNameTitle, wxSizerFlags().Left().Border(wxALL, 5));
	m_pFlexSizer->Add(m_pDescTitle, wxSizerFlags().Left().Border(wxALL, 5));

	// re-initialise the flex sizer to have 3 columns:
	// for the item's name entered by the user, its description, and the checkbox to mark the task as complete
	m_pFlexSizer->Add(m_pItemName, SIZER_FLAGS_LEFT);
	m_pFlexSizer->Add(m_pItemDesc, SIZER_FLAGS_LEFT);
	m_pTopSizer->Add(m_pSettingsSizer, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pFlexSizer, wxSizerFlags().Border(wxLEFT, 20));
}

void TodoItem::SetupPopupMenu()
{
	m_pMenu = new wxMenu();

	m_pMenu->Append(wxID_REMOVE, _T("&Remove Task"));
}

void TodoItem::HandleDelete()
{
	this->GetParent()->Layout();
	this->Destroy();
}

void TodoItem::OnMarkCompleted(wxCommandEvent& e)
{
	m_pTaskList->AddItem(m_taskName);
	this->HandleDelete();
}

void TodoItem::OnRightClick(wxMouseEvent& e)
{
	this->PopupMenu(m_pMenu);
}

void TodoItem::OnRemove(wxCommandEvent& e)
{
	if (wxMessageBox(_T("Are you sure you want to remove this task?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		this->HandleDelete();
	else return;
}

void TodoItem::OnPaint(wxPaintEvent& e)
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(*wxBLACK, 2, wxPENSTYLE_SOLID));
	
	switch (m_nPriorityLevel)
	{
	case 0: // minor
		dc.SetBrush(wxBrush(*wxGREEN, wxBRUSHSTYLE_SOLID));
		break;
	case 1: // medium
		dc.SetBrush(wxBrush(*wxYELLOW, wxBRUSHSTYLE_SOLID));
		break;
	case 2: // major
		dc.SetBrush(wxBrush(*wxRED, wxBRUSHSTYLE_SOLID));
		break;
	}
	
	dc.DrawRectangle(10, m_pNameTitle->GetPosition().y + 3, 10, 10);
}

// =========================================== TaskList ===========================================

TaskList::TaskList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();

	// Bind events
	this->Bind(wxEVT_LIST_ITEM_SELECTED, &TaskList::OnItemSelected, this);
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &TaskList::OnRightClickItem, this);
	m_pMenu->Bind(wxEVT_MENU, &TaskList::OnRemoveItem, this, wxID_REMOVE);
}

TaskList::~TaskList()
{
	// Unbind events
	this->Unbind(wxEVT_LIST_ITEM_SELECTED, &TaskList::OnItemSelected, this);
	this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &TaskList::OnRightClickItem, this);
	m_pMenu->Unbind(wxEVT_MENU, &TaskList::OnRemoveItem, this, wxID_REMOVE);
}

void TaskList::Init()
{
	this->SetupImageList();
	this->SetupColumn();
	this->SetupMenu();
}

void TaskList::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_taskBmp = wxBitmap(path_data::dataDir + _T("\\Images\\check2_small.png"), wxBITMAP_TYPE_PNG);
	m_taskBmp.ResetAlpha();

	m_pImageList->Add(m_taskBmp);
	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void TaskList::SetupColumn()
{
	wxListItem taskCol;
	taskCol.SetText(_T("Completed Tasks"));
	taskCol.SetImage(-1);
	this->InsertColumn(0, taskCol);
	this->SetColumnWidth(0, 200);
}

void TaskList::SetupMenu()
{
	m_pMenu = new wxMenu();

	m_pMenu->Append(wxID_REMOVE, _T("&Remove Item"));
}

void TaskList::AddItem(const wxString& name)
{
	this->InsertItem(0, name, 0);
}

// Events

void TaskList::OnItemSelected(wxListEvent& e)
{
	m_selectionIndex = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	m_currentItemName = GetItemText(m_selectionIndex, 0);
}

void TaskList::OnRightClickItem(wxListEvent& e)
{
	this->PopupMenu(m_pMenu);
}

void TaskList::OnRemoveItem(wxCommandEvent& e)
{
	if (wxMessageBox(_T("Are you sure you want to remove this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		this->DeleteItem(m_selectionIndex);
}

// =========================================== PriorityLevel ===========================================

PriorityLevel::PriorityLevel(wxWindow* parent)
	: wxClientDC{ parent }
{

}