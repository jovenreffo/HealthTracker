#ifndef CALORIELIST_H
#define CALORIELIST_H

#include <wx/wx.h>
#include <wx/listctrl.h>

#include "Nutrient Total/Total.hpp"

class CalorieList : public wxListView
{
private:
	wxMenu* m_pMenu;
	wxImageList* m_pImageList;
	wxBitmap m_calorieBmp;

	Total m_total;

public:
	CalorieList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);
	~CalorieList();

	Total GetTotal() const { return m_total; }
	void AddItem(const wxString& item, const NutrientContent& c);
	void UpdateTotal();
	void HandleDeleteItem();

	// Setup
	void Init();
	void SetupMenu();
	void SetupColumns();
	void SetupImageList();
	void SetupTotalItem();

	// Events
	void OnRightClick(wxListEvent& event);
	void OnDoubleClick(wxListEvent& event);
	void OnDeleteItem(wxCommandEvent& event);
	void OnKey(wxKeyEvent& event);
};

#endif