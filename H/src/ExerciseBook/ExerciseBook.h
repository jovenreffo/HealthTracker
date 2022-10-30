#ifndef _EXERCISEBOOK_H_
#define _EXERCISEBOOK_H_

#include <wx/wx.h>
#include <wx/notebook.h>

#define EXERCISEBOOK_STYLE (wxNB_MULTILINE, wxNB_TOP)

class ExerciseBook: public wxNotebook
{
private:


public:
	ExerciseBook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = EXERCISEBOOK_STYLE);

	// Book setup
	void SetupBitmaps();
	void SetupPanels();
};

#endif