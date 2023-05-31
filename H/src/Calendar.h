#ifndef CALENDAR_H
#define CALENDAR_H

#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/generic/calctrlg.h>
#include <wx/textctrl.h>

#include <vector>

class Calendar; // forward dec

enum class CID // Calendar ID
{
	ID_CAL_DCLICK
};

class CalendarPlanDlg : public wxDialog
{
private:
	// Controls
	wxTextCtrl* m_pTxtCtrl;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizer
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	
	// Validation
	wxString m_txtValue;

public:
	CalendarPlanDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Select date:"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~CalendarPlanDlg();

	const wxString& GetTextValue() const { return m_txtValue; }

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupWindowSizing();
	void SetupConfig();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

class CalendarInfo
{
private:
	wxDateTime m_date;
	wxString m_content;

public:
	CalendarInfo(const wxDateTime& dt, const wxString& content)
		: m_date{ dt }, m_content{ content }
	{ }
	~CalendarInfo() { }

	const wxDateTime& GetDate() const { return m_date; }
	const wxString& GetContent() const { return m_content; }

	void SetDate(const wxDateTime& dt) { m_date = dt; }
	void SetContent(const wxString& content) { m_content = content; }
};

class CalendarPanel : public wxPanel
{
private:
	Calendar* m_pCalendar;
	std::vector<CalendarInfo> m_info;

	wxBoxSizer* m_pTopSizer;

public:
	CalendarPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~CalendarPanel();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
};

class Calendar : public wxGenericCalendarCtrl
{
private:
	wxDateTime m_currDate;
	CalendarPlanDlg* m_pCalPlanDlg;

public:
	Calendar(wxWindow* parent,
		wxWindowID id,
		const wxDateTime& dt = wxDefaultDateTime,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAL_SHOW_HOLIDAYS);
	~Calendar();

	// Calendar events
	void OnSelectDay(wxCalendarEvent& event);
	void OnDoubleClickDay(wxCalendarEvent& event);
};

#endif