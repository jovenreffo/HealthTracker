#include <wx/valtext.h>
#include <wx/statline.h>
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

// =========================================== AddTodoItemDlg ===========================================

AddTodoItemDlg::AddTodoItemDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
}

void AddTodoItemDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void AddTodoItemDlg::SetupControls()
{
}

void AddTodoItemDlg::SetupSizers()
{
}

void AddTodoItemDlg::SetupSizing()
{
	this->SetMinSize(ADDTODOITEMDLG_SIZE);
	this->SetMaxSize(ADDTODOITEMDLG_MAX_SiZE);
	this->SetInitialSize(ADDTODOITEMDLG_SIZE);
}

// =========================================== TodoPanel ===========================================

TodoPanel::TodoPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxScrolled<wxPanel>(parent, id, pos, size, style, _T("todopanel"))
{
	this->Init();
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

// =========================================== TodoItem ===========================================

wxIMPLEMENT_DYNAMIC_CLASS(TodoItem, wxHtmlListBox);

TodoItem::TodoItem(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxPanel(parent, id, pos, size, style)
{
	
}

void TodoItem::Init()
{

}

