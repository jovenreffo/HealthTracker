#ifndef _MEALPLANWINDOW_H_
#define _MEALPLANWINDOW_H_

#include <wx/frame.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/button.h>

#include <vector>

#define MPW_SIZE ( wxSize(440, 280) )
#define MPW_MAX_SIZE ( wxSize() )

#define AMD_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )
#define AMD_SIZE ( wxSize() )
#define AMD_MAX_SIZE ( wxSize() )

enum MPW
{
	ID_ADD_MEAL
};

class AddMealDialog;
class MealDayList;

class MealPlanWindow : public wxFrame
{
private:
	// General window vars
	wxIcon m_mealIcon;
	wxPanel* m_pTopPanel;

	// Controls
	AddMealDialog* m_pAddMealDlg;
	wxButton* m_pAddMeal; wxBitmap m_addBmp;
	wxImageList* m_pImageList;
	std::vector<MealDayList> m_pDayList; // have an individual list for each day of the week.

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pMainSizer;
	wxBoxSizer* m_pDaySizer;

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
	void SetupSizers();
	void SetupLists();

	// Events
	void OnAddMeal(wxCommandEvent& event);
};

class AddMealDialog : public wxDialog
{
private:
	// Controls
	wxTextCtrl* m_pMealNameTxt;
	wxTextCtrl* m_pMealDescTxt;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Controls for day-of-week
	wxChoice* m_pDayChoice;
	wxArrayString m_choiceArr;

	// Validators
	wxString m_mealName;
	wxString m_mealDesc;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxFlexGridSizer* m_pFlexSizer;
	wxBoxSizer* m_pButtonSizer;

public:
	AddMealDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Add Meal"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = AMD_SIZE,
		long style = AMD_STYLE);
	~AddMealDialog();

	// Setup
	void Init();
	void SetupSizing();
	void SetupControls();
	void SetupSizers();

	// Events
};

// MealDayList class will be used only in the AddMealDialog, and not outside.
// Separate class for featured list
// MealList class is for displaying the names of the plans created

class MealDayList : public wxListView 
{
private:
	wxString m_listTitle;

public:
	MealDayList(const wxString& list_title,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);


};

#endif