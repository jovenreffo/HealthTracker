#include <wx/msgdlg.h>
#include "Window.h"
#include "StandardPath.hpp"

// Event table
BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_EXIT, Frame::OnExit)
	EVT_MENU(ID_ENABLE_FULLSCREEN, Frame::OnFullScreen)
	EVT_MENU(wxID_ABOUT, Frame::OnAbout)
	// reset events
	EVT_MENU(wxID_RESET, Frame::OnResetAll)
	EVT_MENU(ID_RESET_ENTRIES, Frame::OnResetEntries)
	EVT_MENU(ID_RESET_WORKOUTS, Frame::OnResetWorkouts)
	EVT_MENU(ID_RESET_ROUTINES, Frame::OnResetRoutines)
END_EVENT_TABLE()

Frame::Frame()
	: wxFrame{ nullptr, -1, _T("Health++"), wxDefaultPosition, WINDOW_SIZE }
{
	this->Init();
}

Frame::~Frame()
{
	this->DestroyChildren();
	delete m_pTaskbarIcon;
}

void Frame::Init()
{
	this->SetupProgramIcon();
	this->SetupTaskbarIcon();
	this->SetupMenuBar();
	this->SetupSizes();
	this->SetupListbook();
}

// Window setup

void Frame::SetupTaskbarIcon()
{
	m_pTaskbarIcon = new TaskbarIcon(this);

	// set the icon
	if (!m_pTaskbarIcon->SetIcon(m_heartIcon, _T("Health++")))
		wxMessageBox(_T("Failed to create taskbar icon."));
	
}

void Frame::SetupProgramIcon()
{
	m_heartIcon = wxIcon(path_data::dataDir + _T("\\Images\\heart.png"), wxBITMAP_TYPE_PNG);
	this->SetIcon(m_heartIcon);
}

void Frame::SetupMenuBar()
{
	m_pMenuBar = new wxMenuBar();
	m_pFileMenu = new wxMenu();
	m_pViewMenu = new wxMenu();
	m_pHelpMenu = new wxMenu();
	m_pResetMenu = new wxMenu();

	// Reset menu to be used with the file menu
	m_pResetMenu->Append(ID_RESET_ENTRIES, _T("&Reset Entry List"));
	m_pResetMenu->Append(ID_RESET_WORKOUTS, _T("&Reset Workout List"));
	m_pResetMenu->Append(ID_RESET_ROUTINES, _T("&Reset Routine List"));
	// File menu
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->AppendSubMenu(m_pResetMenu, _T("&Reset..."));
	m_pFileMenu->Append(wxID_RESET, _T("&Reset All\tCtrl+Shift+R"));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit\tAlt+F4"));

	// View menu
	m_pViewMenu->Append(ID_ENABLE_FULLSCREEN, _T("&Toggle Fullscreen\tF11"));

	// Help menu
	m_pHelpMenu->Append(wxID_ABOUT, _T("&About"));

	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pViewMenu, _T("&View"));
	m_pMenuBar->Append(m_pHelpMenu, _T("&Help"));
	this->SetMenuBar(m_pMenuBar);
}

void Frame::SetupSizes()
{
	this->SetInitialSize(WINDOW_SIZE);
	this->SetMinSize(WINDOW_SIZE);
}

void Frame::SetupListbook()
{
	m_pListbook = new Listbook(this, wxID_ANY);
}

// Events

void Frame::OnExit(wxCommandEvent& WXUNUSED(event))
{
	if (wxMessageBox(_T("Are you sure you want to exit?"), _T("Confirm"), wxYES_NO | wxICON_WARNING) == wxYES)
		this->Close(true);
}

void Frame::OnFullScreen(wxCommandEvent& WXUNUSED(event))
{
	this->ShowFullScreen(!IsFullScreen(), wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
}

void Frame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	m_pAboutDialog = new AboutDialog();
}

void Frame::OnResetAll(wxCommandEvent& WXUNUSED(event))
{

}

void Frame::OnResetEntries(wxCommandEvent& WXUNUSED(event))
{
}

void Frame::OnResetWorkouts(wxCommandEvent& WXUNUSED(event))
{
}

void Frame::OnResetRoutines(wxCommandEvent& WXUNUSED(event))
{
}
