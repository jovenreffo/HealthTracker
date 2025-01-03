#include <wx/msgdlg.h>
#include "Window.h"
#include "StandardPath.hpp"

// Event table
BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_EXIT, Frame::OnExit)
	EVT_MENU(ID_ENABLE_FULLSCREEN, Frame::OnFullScreen)
	EVT_MENU(ID_PREFERENCES, Frame::OnPreferences)
	EVT_MENU(wxID_ABOUT, Frame::OnAbout)
	EVT_MENU(ID_SUBMIT_REPORT, Frame::OnSubmitBugReport)
	// reset events
	EVT_MENU(wxID_RESET, Frame::OnResetAll)
	EVT_MENU(ID_RESET_ENTRIES, Frame::OnResetEntries)
	EVT_MENU(ID_RESET_WORKOUTS, Frame::OnResetWorkouts)
	EVT_MENU(ID_RESET_ROUTINES, Frame::OnResetRoutines)
	EVT_MENU(ID_RESET_LAYOUT, Frame::OnResetWindowLayout)
	// add events
	EVT_MENU(ID_ADD_WORKOUT, Frame::OnAddWorkout)
	EVT_MENU(ID_ADD_ROUTINE, Frame::OnAddRoutine)
	EVT_MENU(ID_ADD_NUTRITION_ITEM, Frame::OnAddNutritonItem)
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
	pConfig->Write("/Frame/x", static_cast<long>(GetPosition().x));
	pConfig->Write("/Frame/y", static_cast<long>(GetPosition().y));
	pConfig->Write("/Frame/w", static_cast<long>(GetClientSize().GetWidth()));
	pConfig->Write("/Frame/h", static_cast<long>(GetClientSize().GetHeight()));
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
	if (m_pConfig == nullptr)
		return;

	// Restore the frame's size and position
	m_pConfig->SetPath(_("/Frame"));

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
#ifdef wxUSE_MENUS
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
	m_pAddMenu->Append(ID_ADD_NUTRITION_ITEM, _T("&Nutritional Item"));
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
	m_pViewMenu->Append(ID_RESET_LAYOUT, _T("&Reset Window Layout\tCtrl+W+R"));

	// Help menu
	m_pHelpMenu->Append(wxID_ABOUT, _T("&About"));
	m_pHelpMenu->Append(ID_SUBMIT_REPORT, _T("Report a bug"));

	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pViewMenu, _T("&View"));
	m_pMenuBar->Append(m_pHelpMenu, _T("&Help"));

#ifdef _DEBUG
	// Tools for debugging and development
	m_pDebugMenu = new wxMenu();

	m_pDebugMenu->Append(ID_WINSIZE, _T("&Get Window Size"));
	m_pDebugMenu->Bind(wxEVT_MENU, &Frame::OnGetWindowSize, this, ID_WINSIZE);

	//m_pMenuBar->Append(m_pDebugMenu, _T("&Debug"));
#endif //_DEBUG

#endif // wxUSE_MENUS

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
	m_pWorkoutList = m_pListbook->GetExerciseBook()->GetNotebook()->GetWorkoutList();
	m_pRoutineList = m_pListbook->GetExerciseBook()->GetNotebook()->GetRoutineList();
	m_pEntryList = m_pListbook->GetJournal()->GetEntryList();
}

void Frame::SetupOther()
{
	// Initialize these here but do not show them until their respective events have been triggered
	m_pPrefsDlg = new PrefsDlg(_T("Health++ Preferences"));
	m_pWorkoutDialog = new WorkoutWindow(m_pWorkoutList, this, wxID_ANY);
	m_pRoutineDialog = new RoutineDialog(m_pWorkoutList->GetContent(), m_pWorkoutList, m_pRoutineList, this, wxID_ANY, _T("New Routine"));
	m_pCaloriePanel = dynamic_cast<CaloriePanel*>(FindWindow(_T("caloriepanel")));
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
	m_pAboutDialog = new AboutDialog(this, wxID_ANY);
	m_pAboutDialog->Show(true);
}

void Frame::OnSubmitBugReport(wxCommandEvent& event)
{
	wxString sendTo = "mailto:jovenreffo@gmail.com";
	
	ShellExecute(NULL, L"open", sendTo.c_str(), L"", L"", 0);
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

void Frame::OnResetWindowLayout(wxCommandEvent& WXUNUSED(event))
{
	Journal* pJournal = m_pListbook->GetJournal();
	pJournal->ResetPerspective();
}

void Frame::OnAddWorkout(wxCommandEvent& WXUNUSED(event))
{
	m_pWorkoutDialog = new WorkoutWindow(m_pWorkoutList, this, wxID_ANY);
	m_pWorkoutDialog->Show(true);
}

void Frame::OnAddRoutine(wxCommandEvent& WXUNUSED(event))
{
	m_pRoutineDialog->Show(true);
}

void Frame::OnAddNutritonItem(wxCommandEvent& WXUNUSED(event))
{
	if (m_pCaloriePanel != nullptr)
		m_pCaloriePanel->AddNewItem();
}

void Frame::OnGetWindowSize(wxCommandEvent& WXUNUSED(event))
{
	wxLogMessage(_T("Width: %d\nHeight: %d"), this->GetSize().GetWidth(), this->GetSize().GetHeight());
}