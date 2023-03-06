#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/valtext.h>
#include <wx/msgdlg.h>

#include "Planning.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"
#include "Flags.hpp"

Calendar::Calendar(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxNotebook(parent, id, pos, size, style, _T("calendar"))
{
	this->Init();
}

void Calendar::Init()
{
	this->SetupImageList();
	this->SetupPages();
}

void Calendar::SetupImageList()
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

void Calendar::SetupPages()
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
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void AddTaskDlg::SetupControls()
{
	m_pTaskNameTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxTextValidator(0, &m_taskName));
	m_pTaskDescTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER, wxTextValidator(0, &m_taskDesc));

	// Set max lengths
	m_pTaskNameTxt->SetMaxLength(75);
	m_pTaskDescTxt->SetMaxLength(200);

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
}

TodoPanel::~TodoPanel()
{
	// Unbind events
	m_pAddButton->Unbind(wxEVT_BUTTON, &TodoPanel::OnAddTask, this);
}

// Panel setup
void TodoPanel::Init()
{
	this->SetupControls();
	this->SetupSizers();
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

	m_pTopButtonSizer->Add(m_pAddButton, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopButtonSizer->Add(m_pClearListButton, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pTopButtonSizer);
#ifdef wxUSE_STATLINE
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
#endif

	// TEST
	TodoItem* pItem = new TodoItem("Make bed", "Wake up at 3am shdfoddshfsfioesfh sieof hseof s", this);

	m_pTopSizer->Add(pItem, wxSizerFlags().Expand().Proportion(1).Border(wxALL, 5));

}

// Events

void TodoPanel::OnAddTask(wxCommandEvent& event)
{
	m_pAddTaskDlg = new AddTaskDlg(this);
	m_pAddTaskDlg->Show(true);

	if (m_pAddTaskDlg->ShowModal() == wxID_OK)
	{

	}
}

// =========================================== TodoItem ===========================================

wxIMPLEMENT_DYNAMIC_CLASS(TodoItem, wxHtmlListBox);

TodoItem::TodoItem(const wxString& taskName, const wxString& taskDesc, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxPanel(parent, id, pos, size, style), m_taskName{ taskName }, m_taskDesc{ taskDesc }
{
	this->Init();
	this->SetBackgroundColour(wxColour(225, 225, 225));

	// Bind events
	m_pMarkCompleted->Bind(wxEVT_CHECKBOX, &TodoItem::OnMarkCompleted, this);
}

TodoItem::~TodoItem()
{
	// Unbind events
	m_pMarkCompleted->Unbind(wxEVT_CHECKBOX, &TodoItem::OnMarkCompleted, this);
}

void TodoItem::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void TodoItem::SetupControls()
{
	m_pMarkCompleted = new wxCheckBox(this, wxID_ANY, _T("Mark as completed"), wxDefaultPosition, wxDefaultSize);

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
	m_pTopSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pFlexSizer = new wxFlexGridSizer(2, wxSize(100, -1));
	this->SetSizerAndFit(m_pTopSizer);

	m_pFlexSizer->Add(m_pNameTitle, wxSizerFlags().Left().Border(wxALL, 5));
	m_pFlexSizer->Add(m_pDescTitle, wxSizerFlags().Left().Border(wxALL, 5));

	// re-initialise the flex sizer to have 3 columns:
	// for the item's name entered by the user, its description, and the checkbox to mark the task as complete
	m_pFlexSizer->Add(m_pItemName, SIZER_FLAGS_LEFT);
	m_pFlexSizer->Add(m_pItemDesc, SIZER_FLAGS_LEFT);
	m_pTopSizer->Add(m_pFlexSizer);
	m_pTopSizer->Add(m_pMarkCompleted, wxSizerFlags().Left().Border(wxLEFT | wxTOP, 30));
}

void TodoItem::OnMarkCompleted(wxCommandEvent& e)
{

}