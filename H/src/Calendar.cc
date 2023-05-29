#include <wx/config.h>
#include "Calendar.h"

CalendarPlanDlg::CalendarPlanDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();

	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &CalendarPlanDlg::OnOK, this);
	m_pCancel->Bind(wxEVT_BUTTON, &CalendarPlanDlg::OnCancel, this);
}

CalendarPlanDlg::~CalendarPlanDlg()
{
	// Unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &CalendarPlanDlg::OnOK, this);
	m_pCancel->Unbind(wxEVT_BUTTON, &CalendarPlanDlg::OnCancel, this);
}

void CalendarPlanDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupConfig();
}

void CalendarPlanDlg::SetupControls()
{
	m_pTxtCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RICH2);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
}

void CalendarPlanDlg::SetupSizers()
{
}

void CalendarPlanDlg::SetupConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/Preferences/"));

	if (pConfig->Read("Spellcheck", 0L) == 1L)
		m_pTxtCtrl->EnableProofCheck(wxTextProofOptions::Default());

	if (pConfig->Read("CheckFont", 0L) == 1L)
	{
		m_pTxtCtrl->SetFont(wxFont(
			pConfig->Read("FontSize", 10L),
			static_cast<wxFontFamily>(pConfig->Read("FontFamily", static_cast<long>(wxFONTFAMILY_DEFAULT))),
			static_cast<wxFontStyle>(pConfig->Read("FontStyle", static_cast<long>(wxFONTSTYLE_NORMAL))),
			wxFONTWEIGHT_NORMAL,
			pConfig->Read("FontUnderline", 0L),
			pConfig->Read("FaceName", "")
		));
	}
}

void CalendarPlanDlg::OnOK(wxCommandEvent& event)
{

}

void CalendarPlanDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

// ===== CalendarPanel =====

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
	// Quick note: for months, indices start at 0.
	// January - 0, February - 1, etc.
	m_currDate = this->GetDate();
#ifdef _DEBUG
	//wxLogMessage(_T("%d\n%d\n%d"), m_currDate.GetYear(), m_currDate.GetMonth(), m_currDate.GetDay());
#endif
}

void Calendar::OnDoubleClickDay(wxCalendarEvent& event)
{
	m_pCalPlanDlg = new CalendarPlanDlg(this, wxID_ANY, wxString(_T("Select date: ")) << m_currDate.FormatDate());
	m_pCalPlanDlg->Show(true);

	if (m_pCalPlanDlg->ShowModal() == wxID_OK)
	{

	}
}
