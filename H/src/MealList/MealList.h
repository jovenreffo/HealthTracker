#ifndef _MEALLIST_H_
#define _MEALLIST_H_

#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/menu.h>

class MealList : public wxListView
{
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

	void AddItem(const wxString& name);

	// Setup
	void Init();
	void SetupImageList();
	void SetupColumn();
	void SetupMenu();

	// Events
	void OnItemRightClick(wxListEvent& event);
	void OnColumnRightClick(wxListEvent& event);
	void OnDeleteItem(wxCommandEvent& event);
};

#endif