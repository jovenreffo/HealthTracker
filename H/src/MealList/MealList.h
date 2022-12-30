#ifndef _MEALLIST_H_
#define _MEALLIST_H_

#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/menu.h>

class MealList : public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxImageList* m_pImageList;
	wxBitmap m_mealBmp;

	wxMenu* m_pMenu;
	wxMenu* m_pColMenu;

public:
	MealList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);
	~MealList();

	void AddItem();

	// Setup
	void Init();
	void SetupImageList();
	void SetupColumn();
	void SetupMenu();

	// Events
	void OnItemRightClick(wxListEvent& event);
	void OnColumnRightClick(wxListEvent& event);
};


#endif