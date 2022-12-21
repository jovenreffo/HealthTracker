#ifndef _MEALPLANWINDOW_H_
#define _MEALPLANWINDOW_H_

#include <wx/frame.h>
#include <wx/bitmap.h>
#include <wx/icon.h>

class MealPlanWindow : public wxFrame
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxIcon m_mealIcon;

public:
	MealPlanWindow(wxWindow* parent = nullptr,
		wxWindowID id = -1,
		const wxString& title = _T("Meal Planner"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE);
	~MealPlanWindow();

	// Setup
	void Init();
	void SetupWindowIcon();
	void SetupSizing();
};

#endif