#ifndef _LISTBOOK_H_
#define _LISTBOOK_H_

#include <wx/listbook.h>
#include <wx/bitmap.h>

#include "Journal.h"
#include "Planning.h"
#include "ExercisePanel.h"
#include "Settings.h"
#include "ClientPanel.h"

class Listbook: public wxListbook
{
private:
	// Tabs
	Journal* m_pJournal;
	Planning* m_pPlanning;
	ExerciseBook* m_pExerciseBook;
	Settings* m_pSettings;
	ClientPanel* m_pClientPanel;

	wxImageList* m_pImageList;
	wxBitmap m_journalBmp;
	wxBitmap m_calendarBmp;
	wxBitmap m_exerciseBmp;
	wxBitmap m_settingsBmp;
	wxBitmap m_clientsBmp;

public:
	Listbook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	ExerciseBook* GetExerciseBook() const { return m_pExerciseBook; }
	Journal* GetJournal() const { return m_pJournal; }

	// Setup
	void SetupBitmaps();
	void SetupTabs();
};

#endif