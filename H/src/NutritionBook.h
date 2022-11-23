#ifndef _CALORIEBOOK_H_
#define _CALORIEBOOK_H_

#include <wx/notebook.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <wx/panel.h>
#include "CaloriePanel.h"

class NutritionBook: public wxNotebook
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxImageList* m_pImageList;
	wxBitmap m_calorieBmp;

	CaloriePanel* m_pCaloriePanel;

public:
	NutritionBook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	~NutritionBook();

	// Setup
	void Init();
	void SetupImageList();
	void SetupCaloriePanel();
	void SetupPages();
};

#endif