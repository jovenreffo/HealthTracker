#include <wx/config.h>
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
	// Load config
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_("/Preferences"));

	if (pConfig->Read(_T("ColourSelection"), 0L) == 0) // default: black
	{
		m_journalBmp = wxBitmap(path_data::dataDir + _T("\\Images\\journal.png"), wxBITMAP_TYPE_PNG);
		m_exerciseBmp = wxBitmap(path_data::dataDir + _T("\\Images\\exercise.png"), wxBITMAP_TYPE_PNG);
		m_calendarBmp = wxBitmap(path_data::dataDir + _T("\\Images\\calendar.png"), wxBITMAP_TYPE_PNG);
		m_settingsBmp = wxBitmap(path_data::dataDir + _T("\\Images\\misc.png"), wxBITMAP_TYPE_PNG);
		m_clientsBmp = wxBitmap(path_data::dataDir + _T("\\Images\\clients.png"), wxBITMAP_TYPE_PNG);

		m_journalBmp.ResetAlpha();
		m_calendarBmp.ResetAlpha();
		m_journalBmp.ResetAlpha();
		m_settingsBmp.ResetAlpha();
		m_clientsBmp.ResetAlpha();
	}
	else if (pConfig->Read(_T("ColourSelection"), 0L) == 1) // red
	{
		m_journalBmp = wxBitmap(path_data::dataDir + _T("\\Images\\journal_red.png"), wxBITMAP_TYPE_PNG);
		m_exerciseBmp = wxBitmap(path_data::dataDir + _T("\\Images\\exercise_red.png"), wxBITMAP_TYPE_PNG);
		m_calendarBmp = wxBitmap(path_data::dataDir + _T("\\Images\\calendar_red.png"), wxBITMAP_TYPE_PNG);
		m_settingsBmp = wxBitmap(path_data::dataDir + _T("\\Images\\misc_red.png"), wxBITMAP_TYPE_PNG);
		m_clientsBmp = wxBitmap(path_data::dataDir + _T("\\Images\\clients.png"), wxBITMAP_TYPE_PNG);

		m_journalBmp.ResetAlpha();
		m_calendarBmp.ResetAlpha();
		m_journalBmp.ResetAlpha();
		m_settingsBmp.ResetAlpha();
		m_clientsBmp.ResetAlpha();
	}

	// Set up the image list to be used with the listbook
	m_pImageList = new wxImageList(38, 38);
	m_pImageList->Add(m_journalBmp);
	m_pImageList->Add(m_exerciseBmp);
	m_pImageList->Add(m_calendarBmp);
	m_pImageList->Add(m_settingsBmp);
	m_pImageList->Add(m_clientsBmp);
}

void Listbook::SetupTabs()
{
	this->AssignImageList(m_pImageList);
	this->Show(true);

	m_pJournal = new Journal(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pPlanning = new Planning(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pExerciseBook = new ExerciseBook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pSettings = new Settings(m_pExerciseBook, m_pJournal, this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pClientPanel = new ClientPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// Add tabs to the list
	this->AddPage(m_pJournal, _T("Journal"), true, 0);
	this->AddPage(m_pExerciseBook, _T("Activity"), false, 1);
	this->AddPage(m_pPlanning, _T("Planning"), false, 2);
	this->AddPage(m_pSettings, _T("Miscellaneous"), false, 3);
	this->AddPage(m_pClientPanel, _T("Client List"), false, 4);
}
