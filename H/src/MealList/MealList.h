#ifndef _MEALLIST_H_
#define _MEALLIST_H_

#include <wx/listctrl.h>

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

	void AddItem();

	// Setup
	void Init();
	void SetupImageList();
	void SetupColumn();
	void SetupMenu();


};


#endif