#ifndef _NUTRITIONPANEL_H_
#define _NUTRITIONPANEL_H_

#include <wx/panel.h>
#include <wx/sizer.h>
#include "NutritionBook.h"

class NutritionPanel: public wxPanel
{
private:
	NutritionBook* m_pNutrBook;
	wxBoxSizer* m_pBoxSizer;

public:
	NutritionPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Setup
	void Init();
	void SetupNutritionBook();
	void SetupSizers();
};

#endif