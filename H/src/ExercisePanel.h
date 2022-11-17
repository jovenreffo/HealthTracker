#ifndef _EXERCISEPANEL_H_
#define _EXERCISEPANEL_H_

#include <wx/panel.h>
#include "ExerciseBook.h"

class ExercisePanel : public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	ExerciseBook* m_pExerciseBook;

	wxBoxSizer* m_pBoxSizer;

public:
	ExercisePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	ExerciseBook* GetExerciseBook() const { return m_pExerciseBook; }

	// Setup
	void Init();
	void SetupExerciseBook();
	void SetupSizers();
};

#endif