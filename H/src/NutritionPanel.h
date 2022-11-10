#ifndef _NUTRITIONPANEL_H_
#define _NUTRITIONPANEL_H_

#include <wx/panel.h>

class NutritionPanel: public wxPanel
{
public:
	NutritionPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif