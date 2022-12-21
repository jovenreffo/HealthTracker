#ifndef _MEALPLANWINDOW_H_
#define _MEALPLANWINDOW_H_

#include <wx/frame.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/dialog.h>
#include <wx/button.h>

#define MPW_SIZE	 ( wxSize(440, 280) )
#define MPW_MAX_SIZE ( wxSize() )

#define AMD_STYLE	 ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )
#define AMD_SIZE	 ( wxSize() )
#define AMD_MAX_SIZE ( wxSize() )

enum MPW
{
	ID_ADD_MEAL
};

class AddMealDialog;

class MealPlanWindow : public wxFrame
{
private:
	DECLARE_EVENT_TABLE()

private:
	// General window vars
	wxIcon m_mealIcon;

	// Controls
	AddMealDialog* m_pAddMealDlg;
	wxButton* m_pAddMeal; wxBitmap m_addBmp;
	wxImageList* m_pImageList;
	wxListView* m_pDayList;

public:
	MealPlanWindow(wxWindow* parent = nullptr,
		wxWindowID id = -1,
		const wxString& title = _T("Meal Planner"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = MPW_SIZE,
		long style = wxDEFAULT_FRAME_STYLE);
	~MealPlanWindow();

	// Setup
	void Init();
	void SetupWindowIcon();
	void SetupSizing();
	void SetupControls();

	// Events
	void OnAddMeal(wxCommandEvent& event);
};

class AddMealDialog : public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

public:
	AddMealDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Add Meal"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = AMD_SIZE,
		long style = AMD_STYLE);
	~AddMealDialog();

	// Setup

	// Events
};

#endif