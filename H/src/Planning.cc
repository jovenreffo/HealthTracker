#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/valtext.h>

#include "Planning.h"
#include "StandardPath.hpp"

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
}

AddTaskDlg::~AddTaskDlg()
{
	// Unbind events
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
	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Left().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().Left().Border(wxALL, 5));
}

void AddTaskDlg::SetupSizing()
{
	this->SetInitialSize(ADDTASKDLG_SIZE);
	this->SetMinSize(ADDTASKDLG_SIZE);
	this->SetMaxSize(ADDTASKDLG_MAX_SIZE);
}

// events

void AddTaskDlg::OnTextEnter(wxCommandEvent& e)
{

}

void AddTaskDlg::OnOK(wxCommandEvent& e)
{

}

void AddTaskDlg::OnCancel(wxCommandEvent& e)
{

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
	m_pAddButton = new wxButton(this, static_cast<int>(TD::ID_ADD_TODO), _T("Add Task"), wxDefaultPosition, wxDefaultSize);
	m_pAddButton->SetBitmap(m_addBmp);
}

void TodoPanel::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopSizer->Add(m_pAddButton, wxSizerFlags().Left().Border(wxALL, 5));
#ifdef wxUSE_STATLINE
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
#endif
}

// Events
void TodoPanel::OnTextEnter(wxCommandEvent& event)
{

}

void TodoPanel::OnAddTask(wxCommandEvent& event)
{
	m_pAddTaskDlg = new AddTaskDlg(this);
	m_pAddTaskDlg->Show(true);
}

// =========================================== TodoItem ===========================================

wxIMPLEMENT_DYNAMIC_CLASS(TodoItem, wxHtmlListBox);

TodoItem::TodoItem(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxPanel(parent, id, pos, size, style)
{
	
}

void TodoItem::Init()
{

}

