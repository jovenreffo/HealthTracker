#include "Window.h"
#include "StandardPath.hpp"

// Event table
BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_EXIT, Frame::OnExit)
	EVT_MENU(ID_FULLSCREEN, Frame::OnFullScreen)
END_EVENT_TABLE()

Frame::Frame()
	: wxFrame{ nullptr, -1, _T("Health Trackr"), wxDefaultPosition, WINDOW_SIZE }
{
	this->Init();
}

void Frame::Init()
{
	this->SetupMenuBar();
	this->SetupSizes();
	this->SetupBitmaps();
	this->SetupListbook();
}

// Window setup

void Frame::SetupMenuBar()
{
	m_pMenuBar = new wxMenuBar();
	m_pFileMenu = new wxMenu();
	m_pViewMenu = new wxMenu();

	// File menu
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit\tAlt+F4"));

	// View menu
	m_pViewMenu->Append(ID_FULLSCREEN, _T("&Toggle Fullscreen\tF11"));

	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pViewMenu, _T("&View"));
	this->SetMenuBar(m_pMenuBar);
}

void Frame::SetupSizes()
{
	this->SetInitialSize(WINDOW_SIZE);
	this->SetMinSize(WINDOW_SIZE);
}

void Frame::SetupBitmaps()
{
	m_journalBmp = wxBitmap(path_data::dataDir + _T("\\Images\\journal.png"), wxBITMAP_TYPE_PNG);
	m_calendarBmp = wxBitmap(path_data::dataDir + _T("\\Images\\calendar.png"), wxBITMAP_TYPE_PNG);
	m_exerciseBmp = wxBitmap(path_data::dataDir + _T("\\Images\\exercise.png"), wxBITMAP_TYPE_PNG);
	m_settingsBmp = wxBitmap(path_data::dataDir + _T("\\Images\\settings.png"), wxBITMAP_TYPE_PNG);

	// Set up the image list to be used with the listbook
	m_pImageList = new wxImageList(38, 38);
	m_pImageList->Add(m_journalBmp);
	m_pImageList->Add(m_calendarBmp);
	m_pImageList->Add(m_exerciseBmp);
	m_pImageList->Add(m_settingsBmp);
}

void Frame::SetupListbook()
{
	m_pListbook = new Listbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pListbook->AssignImageList(m_pImageList);
	m_pListbook->Show(true);

	m_pJournal = new Journal(m_pListbook, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pCalendar = new Calendar(m_pListbook, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pSettings = new Settings(m_pListbook, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pExercisePanel = new ExercisePanel(m_pListbook, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// Add tabs to the list
	m_pListbook->AddPage(m_pJournal, _T("Journal"), true, 0);
	m_pListbook->AddPage(m_pCalendar, _T("Calendar"), false, 1);
	m_pListbook->AddPage(m_pExercisePanel, _T("Exercise"), false, 2);
	m_pListbook->AddPage(m_pSettings, _T("Settings"), false, 3);
}

// Events

void Frame::OnExit(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to exit?"), _T("Confirm"), wxYES_NO | wxICON_WARNING) == wxYES)
		this->Close(true);
}

void Frame::OnFullScreen(wxCommandEvent& event)
{
	this->ShowFullScreen(!IsFullScreen(), wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
}