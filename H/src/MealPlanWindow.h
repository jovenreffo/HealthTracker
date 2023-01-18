#ifndef _MEALPLANWINDOW_H_
#define _MEALPLANWINDOW_H_

#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/icon.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/checkbox.h>

#include <vector>
#include "MealList/MealList.h"
#include "MealPlanInfo/MealPlanInfo.hpp"

#define MPW_SIZE ( wxSize(640, 280) )
#define MPW_MAX_SIZE ( wxSize(1050, 500) )

#define DLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )

#define AMD_SIZE ( wxSize(340, 250) )
#define AMD_MAX_SIZE ( wxSize(390, 285) )

#define SMPD_SIZE ( wxSize(280, 180) )
#define SMPD_MAX_SIZE ( wxSize(320, 200) )

enum MPW
{
	ID_ADD_MEAL,
	ID_SAVE_PLAN
};

class SaveMealPlanDialog;
class AddMealDialog;
class MealDayList;

class MealPlanWindow : public wxFrame
{
private:
	// General window vars
	wxIcon m_mealIcon;
	wxPanel* m_pTopPanel;
	MealList* m_pMealList;
	wxArrayString m_daysOfWeek;
	MealPlanInfo m_mealPlanInfo;

	// Controls
	SaveMealPlanDialog* m_pSavePlanDlg;
	AddMealDialog* m_pAddMealDlg;
	wxButton* m_pAddMeal; wxBitmap m_addBmp;
	wxButton* m_pSavePlan; wxBitmap m_saveBmp;
	std::vector<MealDayList*> m_pDayList; // Have an individual list for each day of the week.

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxBoxSizer* m_pMainSizer;
	wxBoxSizer* m_pDaySizer;

public:
	MealPlanWindow(MealList* pMealList,
		wxWindow* parent = nullptr,
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
	void OnSavePlan(wxCommandEvent& event);
};

class SaveMealPlanDialog : public wxDialog
{
private:
	// Controls
	wxTextCtrl* m_pPlanNameTxt;
	wxCheckBox* m_pSetFeatured;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pHorizontalSizer;

	// Validator
	wxString m_planName;
	bool m_bSetFeatured;

public:
	SaveMealPlanDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Save Meal Plan"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = DLG_STYLE);
	~SaveMealPlanDialog();

	const wxString& GetPlanName() const { return m_planName; }
	bool GetFeaturedState() const { return m_bSetFeatured; }

	// Setup
	void Init();
	void SetupSizing();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
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
	int m_choiceValue;

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
		long style = DLG_STYLE);
	~AddMealDialog();

	// Getters for validators
	wxChoice* GetChoiceCtrl() { return m_pDayChoice; }
	const wxString& GetMealName() const { return m_mealName; }
	const wxString& GetMealDesc() const { return m_mealDesc; }
	wxString GetChoiceStr() const { return m_pDayChoice->GetStringSelection(); }
	const int GetChoiceValue() const { return m_choiceValue; }

	// Setup
	void Init();
	void SetupSizing();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnUpdateOK(wxUpdateUIEvent& event);
};

// MealDayList class will be used only in the MealPlanWindow, and not outside.
// Separate class for featured list
// MealList class is for displaying the names of the plans created

class MealDayList : public wxListView 
{
private:
	wxString m_listTitle;

	wxImageList* m_pImageList;
	wxBitmap m_mealBmp;

	wxMenu* m_pMenu;
	wxMenu* m_pColMenu;

public:
	MealDayList(const wxString& list_title,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);
	~MealDayList();

	const wxString& GetListTitle() const { return m_listTitle; }

	// Setup
	void Init();
	void SetupColumn();
	void SetupMenu();
	void SetupImageList();

	void ResetList();
	void AddItem(const wxString& name);

	// Events
	void OnRightClickItem(wxListEvent& event);
	void OnRightClickColumn(wxListEvent& event);
	void OnDeleteItem(wxCommandEvent& event);
	void OnViewItem(wxCommandEvent& event);
	void OnResetList(wxCommandEvent& event);
};

#endif