#ifndef _CALORIEBOOK_H_
#define _CALORIEBOOK_H_

#include <wx/notebook.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <wx/panel.h>
#include "CaloriePanel.h"
#include "MealPlan.h"

class NutritionBook: public wxNotebook
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxImageList* m_pImageList;
	wxBitmap m_calorieBmp;
	wxBitmap m_mealBmp;

	CaloriePanel* m_pCaloriePanel;
	MealPlan* m_pMealPlan;

public:
	NutritionBook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	~NutritionBook();

	CaloriePanel* GetCaloriePanel() const { return m_pCaloriePanel; }

	// Setup
	void Init();
	void SetupImageList();
	void SetupCaloriePanel();
	void SetupMealPlan();
	void SetupPages();
};

#endif