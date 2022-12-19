#ifndef _MEALPLAN_H_
#define _MEALPLAN_H_

#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/bitmap.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/splitter.h>

enum class MP
{
	ID_ADD_PLAN,
	ID_MEAL_LIST,
	ID_FEATURED_LIST,
	ID_PANEL_SPLITTER
};

class MealList;

class MealPlan : public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	// Controls
	wxButton* m_pAddMeal; wxBitmap m_addBmp;
	MealList* m_pMealList;
	wxListView* m_pFeaturedList;
	
	// Panels
	wxSplitterWindow* m_pSplitter;
	wxPanel* m_pPlansPanel;
	wxPanel* m_pFeaturedPanel;

	// sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pListSizer;
	wxStaticBoxSizer* m_pPlansList;
	wxStaticBoxSizer* m_pFeaturedPlan;

public:
	MealPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Panel setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSplitter();
	void SetupPanels();

	// Events

};

class MealList : public wxListView
{
private:
	DECLARE_EVENT_TABLE()

public:
	MealList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);
};

#endif