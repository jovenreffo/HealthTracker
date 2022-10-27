#pragma once

#include <wx/wx.h>
#include "ListBook.h"
#include "Journal.h"
#include "Calendar.h"

class App : public wxApp
{
public:
	virtual bool OnInit();
};

#define WINDOW_SIZE (wxSize(640, 480))

class Frame : public wxFrame
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenuBar* m_pMenuBar;
	wxMenu* m_pFileMenu;

	// Navigation tabs
	Journal* m_pJournal;
	Calendar* m_pCalendar;

	Listbook* m_pListbook;
	wxImageList* m_pImageList;
	wxBitmap m_journalBmp;
	wxBitmap m_calendarBmp;
	wxBitmap m_exerciseBmp;

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
};