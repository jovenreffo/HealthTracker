#include <wx/msgdlg.h>
#include "Window.h"
#include "StandardPath.hpp"

// Event table
BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_EXIT, Frame::OnExit)
	EVT_MENU(ID_ENABLE_FULLSCREEN, Frame::OnFullScreen)
	EVT_MENU(wxID_ABOUT, Frame::OnAbout)
	EVT_MENU(ID_PREFERENCES, Frame::OnPreferences)
	// reset events
	EVT_MENU(wxID_RESET, Frame::OnResetAll)
	EVT_MENU(ID_RESET_ENTRIES, Frame::OnResetEntries)
	EVT_MENU(ID_RESET_WORKOUTS, Frame::OnResetWorkouts)
	EVT_MENU(ID_RESET_ROUTINES, Frame::OnResetRoutines)
	// add events
	EVT_MENU(ID_ADD_WORKOUT, Frame::OnAddWorkout)
	EVT_MENU(ID_ADD_ROUTINE, Frame::OnAddRoutine)
END_EVENT_TABLE()

Frame::Frame()
	: wxFrame{ nullptr, -1, _T("Health++"), wxDefaultPosition, WINDOW_SIZE }
{
	this->Init();
	this->InitConfig();
}

Frame::~Frame()
{
	this->DestroyChildren();
	delete m_pTaskbarIcon;

	wxConfigBase* pConfig = wxConfigBase::Get();
	if (!pConfig)
		return;

	// Save the window's position and size
	int x, y, w, h;
	GetClientSize(&w, &h);
	GetPosition(&x, &y);
	pConfig->Write("/Frame/x", static_cast<long>(x));
	pConfig->Write("/Frame/y", static_cast<long>(y));
	pConfig->Write("/Frame/w", static_cast<long>(w));
	pConfig->Write("/Frame/h", static_cast<long>(h));
}

bool Frame::ConfirmReset()
{
	if (wxMessageBox(_T("Are you sure you want to reset this list?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		return true;
	else
		return false;
}

void Frame::Init()
{
	this->SetupProgramIcon();
	this->SetupTaskbarIcon();
	this->SetupMenuBar();
	this->SetupSizes();
	this->SetupListbook();
	this->SetupLists();
	this->SetupOther();
}

void Frame::InitConfig()
{
	m_pConfig = wxConfigBase::Get();

	// Restore the frame's size
	m_pConfig->SetPath("Frame");

	this->Move(m_pConfig->Read("x", 100),
			   m_pConfig->Read("y", 100));

	this->SetClientSize(m_pConfig->Read("w", 640),
						m_pConfig->Read("h", 480));
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
	m_pEditMenu = new wxMenu();
	m_pViewMenu = new wxMenu();
	m_pHelpMenu = new wxMenu();
	m_pResetMenu = new wxMenu();
	m_pAddMenu = new wxMenu();

	// Reset menu to be used with the file menu
	m_pResetMenu->Append(ID_RESET_ENTRIES, _T("&Reset Entry List"));
	m_pResetMenu->Append(ID_RESET_WORKOUTS, _T("&Reset Workout List"));
	m_pResetMenu->Append(ID_RESET_ROUTINES, _T("&Reset Routine List"));
	// Add menu to be used with the file menu
	m_pAddMenu->Append(ID_ADD_WORKOUT, _T("&New Workout"));
	m_pAddMenu->Append(ID_ADD_ROUTINE, _T("&New Routine"));
	// File menu
	m_pFileMenu->AppendSubMenu(m_pAddMenu, _T("&Add..."));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->AppendSubMenu(m_pResetMenu, _T("&Reset..."));
	m_pFileMenu->Append(wxID_RESET, _T("&Reset All\tCtrl+Shift+R"));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(ID_PREFERENCES, _T("&Preferences...\tCtrl+P"));
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

void Frame::SetupLists()
{
	m_pWorkoutList = m_pListbook->GetExercisePanel()->GetExerciseBook()->GetNotebook()->GetWorkoutList();
	m_pRoutineList = m_pListbook->GetExercisePanel()->GetExerciseBook()->GetNotebook()->GetRoutineList();
	m_pEntryList = m_pListbook->GetJournal()->GetEntryList();
}

void Frame::SetupOther()
{
	// Initialize these here but do not show them until their respective events have been triggered
	m_pPrefsDlg = new PrefsDlg(_T("Preferences"));
	m_pWorkoutWindow = new WorkoutWindow(this, wxID_ANY, m_pListbook->GetExercisePanel()->GetExerciseBook()->GetNotebook()->GetWorkoutList());
	m_pRoutineDialog = new RoutineDialog(m_pWorkoutList->GetContent(), m_pRoutineList, this, wxID_ANY, _T("New Routine"));
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

void Frame::OnPreferences(wxCommandEvent& event)
{
	m_pPrefsDlg->Show(this);
}

// class hierarchy reference for accessing the lists: (doing it this way to prevent use of global vars)
// listbook -> exercisepanel -> exercisebook -> wpnotebook

void Frame::OnResetAll(wxCommandEvent& WXUNUSED(event))
{
	if (wxMessageBox(_T("Are you sure you want to delete all of your saved items?"), _T("Confirm"), wxYES_NO | wxICON_WARNING) == wxYES)
	{
		m_pEntryList->DeleteAllItems();
		m_pWorkoutList->DeleteAllItems();
		m_pRoutineList->DeleteAllItems();
	}
}

void Frame::OnResetEntries(wxCommandEvent& WXUNUSED(event))
{
	if (ConfirmReset())
		m_pEntryList->DeleteAllItems();
}

void Frame::OnResetWorkouts(wxCommandEvent& WXUNUSED(event))
{
	if (ConfirmReset())
		m_pWorkoutList->DeleteAllItems();
}

void Frame::OnResetRoutines(wxCommandEvent& WXUNUSED(event))
{
	if (ConfirmReset())
		m_pRoutineList->DeleteAllItems();
}

void Frame::OnAddWorkout(wxCommandEvent& WXUNUSED)
{
	m_pWorkoutWindow->Show(true);
}

void Frame::OnAddRoutine(wxCommandEvent& WXUNUSED)
{
	m_pRoutineDialog->Show(true);
}
