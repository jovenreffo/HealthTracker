#pragma once

#include <wx/wx.h>
#include "ListBook.h"
#include "Journal.h"
#include "Calendar.h"
#include "Settings.h"
#include "ExercisePanel.h"
#include "ExerciseBook.h"
#include "AboutDialog/AboutDialog.h"
#include "TaskbarIcon.h"
#include "xpm/xpm_include.h"

class App : public wxApp
{
public:
	virtual bool OnInit();
};

#define WINDOW_SIZE (wxSize(640, 480))

enum
{
	ID_ENABLE_FULLSCREEN
};

class Frame : public wxFrame
{
private:
	DECLARE_EVENT_TABLE()

private:
	// Menu bar
	wxMenuBar* m_pMenuBar;
	wxMenu* m_pFileMenu;
	wxMenu* m_pViewMenu;
	wxMenu* m_pHelpMenu;

	// Navigation tabs
	Journal* m_pJournal;
	Calendar* m_pCalendar;
	ExercisePanel* m_pExercisePanel;
	Settings* m_pSettings;
	// Images
	Listbook* m_pListbook;
	wxImageList* m_pImageList;
	wxBitmap m_journalBmp;
	wxBitmap m_calendarBmp;
	wxBitmap m_exerciseBmp;
	wxBitmap m_settingsBmp;

	AboutDialog* m_pAboutDialog;

	wxIcon m_heartIcon;
	TaskbarIcon* m_pTaskbarIcon;
	
public:
	Frame();
	~Frame();

	// Window setup
	void Init();
	void SetupTaskbarIcon();
	void SetupProgramIcon();
	void SetupMenuBar();
	void SetupSizes();
	void SetupListbook();

	// Events
	void OnExit(wxCommandEvent& event);
	void OnFullScreen(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};