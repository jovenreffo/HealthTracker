#ifndef _EXERCISEPANEL_H_
#define _EXERCISEPANEL_H_

#include <wx/panel.h>

class ExercisePanel : public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

public:
	ExercisePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif