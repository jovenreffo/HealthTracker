#include "ListBook.h"
#include "StandardPath.hpp"

Listbook::Listbook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListbook(parent, id, pos, size, style)
{
	this->SetupBitmaps();
	this->SetupTabs();
}

void Listbook::SetupBitmaps()
{
	m_journalBmp = wxBitmap(path_data::dataDir + _T("\\Images\\journal.png"), wxBITMAP_TYPE_PNG);
	m_exerciseBmp = wxBitmap(path_data::dataDir + _T("\\Images\\exercise.png"), wxBITMAP_TYPE_PNG);
	m_calendarBmp = wxBitmap(path_data::dataDir + _T("\\Images\\calendar.png"), wxBITMAP_TYPE_PNG);
	m_settingsBmp = wxBitmap(path_data::dataDir + _T("\\Images\\settings.png"), wxBITMAP_TYPE_PNG);

	m_journalBmp.ResetAlpha();
	m_calendarBmp.ResetAlpha();
	m_journalBmp.ResetAlpha();
	m_settingsBmp.ResetAlpha();

	// Set up the image list to be used with the listbook
	m_pImageList = new wxImageList(38, 38);
	m_pImageList->Add(m_journalBmp);
	m_pImageList->Add(m_exerciseBmp);
	m_pImageList->Add(m_calendarBmp);
	m_pImageList->Add(m_settingsBmp);
}

void Listbook::SetupTabs()
{
	this->AssignImageList(m_pImageList);
	this->Show(true);

	m_pJournal = new Journal(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pCalendar = new Calendar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pExercisePanel = new ExercisePanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pSettings = new Settings(m_pExercisePanel, m_pJournal, this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// Add tabs to the list
	this->AddPage(m_pJournal, _T("Journal"), true, 0);
	this->AddPage(m_pExercisePanel, _T("Activity"), false, 1);
	this->AddPage(m_pCalendar, _T("Calendar"), false, 2);
	this->AddPage(m_pSettings, _T("Settings"), false, 3);
}
