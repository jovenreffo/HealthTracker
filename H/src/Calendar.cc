#include "Calendar.h"

CalendarPanel::CalendarPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style, _T("caloriepanel"))
{
	this->Init();
}

CalendarPanel::~CalendarPanel()
{
}

void CalendarPanel::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void CalendarPanel::SetupControls()
{
	m_pCalendar = new Calendar(this, wxID_ANY);
	m_pCalendar->Show(true);
}

void CalendarPanel::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopSizer->Add(m_pCalendar, wxSizerFlags().Expand().Proportion(0).Border(wxALL, 5));
}

// ====== CalendarCtrl ======

Calendar::Calendar(wxWindow* parent, wxWindowID id, const wxDateTime& dt, const wxPoint& pos, const wxSize& size, long style)
	: wxGenericCalendarCtrl(parent, id, dt, pos, size, style)
{
	// Bind events
	this->Bind(wxEVT_CALENDAR_DAY_CHANGED, &Calendar::OnSelectDay, this);
	this->Bind(wxEVT_CALENDAR_DOUBLECLICKED, &Calendar::OnDoubleClickDay, this);
}

Calendar::~Calendar()
{
	// Unbind events
	this->Unbind(wxEVT_CALENDAR_DAY_CHANGED, &Calendar::OnSelectDay, this);
	this->Unbind(wxEVT_CALENDAR_DOUBLECLICKED, &Calendar::OnDoubleClickDay, this);
}

void Calendar::OnSelectDay(wxCalendarEvent& event)
{
}

void Calendar::OnDoubleClickDay(wxCalendarEvent& event)
{
	wxLogMessage(_T("Dclick"));
}