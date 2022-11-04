#pragma once

#include <wx/wx.h>
#include "ListBook.h"
#include "Journal.h"
#include "Calendar.h"
#include "Settings.h"
#include "ExercisePanel.h"
#include "ExerciseBook.h"

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
	
public:
	Frame();

	// Window setup
	void Init();
	void SetupMenuBar();
	void SetupSizes();
	void SetupBitmaps();
	void SetupListbook();

	// Events
	void OnExit(wxCommandEvent& event);
	void OnFullScreen(wxCommandEvent& event);
};