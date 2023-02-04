#ifndef _MEALPLAN_H_
#define _MEALPLAN_H_

#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/bitmap.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/splitter.h>

#include <vector>

#include "MealPlanWindow.h"
#include "MealList/MealList.h"

enum class MP
{
	ID_ADD_PLAN,
	ID_MEAL_LIST,
	ID_FEATURED_LIST,
	ID_PANEL_SPLITTER,
	ID_CHANGE_FEATURED_LIST
};

class FeaturedList;
class ChangeFeaturedDialog;

class MealPlan : public wxSplitterWindow
{
private:
	DECLARE_EVENT_TABLE()

private:
	// Controls
	wxButton* m_pAddMeal; wxBitmap m_addBmp;
	wxButton* m_pChangeFeatured; wxBitmap m_changeBmp;
	MealList* m_pMealList;
	FeaturedList* m_pFeaturedList;
	ChangeFeaturedDialog* m_pChangeFeaturedPlanDlg;

	MealPlanWindow* m_pMealPlanWin;
	std::vector<MealPlanInfo> m_mealPlanInfoVec;
	
	// Panels
	wxPanel* m_pPlansPanel;
	wxPanel* m_pFeaturedPanel;

	// sizers
	wxStaticBoxSizer* m_pPlansSizer;
	wxStaticBoxSizer* m_pFeaturedSizer;

public:
	MealPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxSP_THIN_SASH | wxSP_LIVE_UPDATE | wxSP_NOBORDER);

	// Panel setup
	void Init();
	void SetupSplitter();
	void SetupControls();
	void SetupSizers();
	void SetupPanels();

	// Events
	void OnAddMealPlan(wxCommandEvent& event);
	void OnChangeFeaturedPlan(wxCommandEvent& event);
	void OnCloseMealPlanWindow(wxCloseEvent& event);
};

class FeaturedList : public wxListView
{
private:
	wxArrayString m_daysOfWeek;

public:
	FeaturedList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);
	~FeaturedList();

	// Setup
	void Init();
	void SetupColumns();
	void SetupFeaturedItems(const std::vector<MealPlanInfo>& mealPlanInfoVec);

	// Events
	void OnDragColumns(wxListEvent& event);
};

#define CFD_SIZE (wxSize(250, 150))
#define CFD_MAX_SIZE (wxSize(325, 185))

class ChangeFeaturedDialog : public wxDialog
{
private:
	// Controls
	wxChoice* m_pMealChoice;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxFlexGridSizer* m_pHorizontalSizer;

	// Validator
	int m_mealChoice;

	MealList* m_pMealList;
	wxArrayString m_mealStrings;

public:
	ChangeFeaturedDialog(MealList* pMealList,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = CFD_SIZE,
		long style = DLG_STYLE);
	~ChangeFeaturedDialog();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};

#endif