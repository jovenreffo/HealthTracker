#include <wx/valtext.h>
#include "Calendar.h"
#include "StandardPath.hpp"

// Event table for the Calendar base notebook
BEGIN_EVENT_TABLE(Calendar, wxNotebook)

END_EVENT_TABLE()

// CalendarPanel
BEGIN_EVENT_TABLE(CalendarPanel, wxPanel)

END_EVENT_TABLE()

// TodoPanel
BEGIN_EVENT_TABLE(TodoPanel, wxPanel)

END_EVENT_TABLE()

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

// =========================================== TodoPanel ===========================================

TodoPanel::TodoPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style, _T("todopanel"))
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
	m_pAddButton = new wxButton(this, static_cast<int>(TD::ID_ADD_TODO), _T("Add Task"), wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pAddButton->SetBitmap(m_addBmp);
}

void TodoPanel::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pTextSizer = new wxFlexGridSizer(3, wxSize(5, 1));
	m_pObjectiveSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("Today's Objectives"));

	// Control setup
	m_pTextSizer->Add(m_pAddButton, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));

	// Arrangement
	this->SetSizerAndFit(m_pTopSizer);
	m_pTopSizer->Add(m_pTextSizer);
	m_pTopSizer->Add(m_pObjectiveSizer);
}

// Splitter setup


// Events
void TodoPanel::OnTextEnter(wxCommandEvent& event)
{

}