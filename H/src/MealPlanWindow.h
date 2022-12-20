#ifndef _MEALPLANWINDOW_H_
#define _MEALPLANWINDOW_H_

#include <wx/frame.h>

class MealPlanWindow : public wxFrame
{
private:
	DECLARE_EVENT_TABLE()

public:
	MealPlanWindow(wxWindow* parent = nullptr,
		wxWindowID id = -1,
		const wxString& title = _T("Meal Planner"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE);
	~MealPlanWindow();
};

#endif