#ifndef NUTRITIONCATALOG_H
#define NUTRITIONCATALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <vector>

#define NC_SIZE (wxSize(640, 480))

class CatalogItem
{
private:
	// Information about the item
	wxString m_name;
	wxBitmap m_itemBmp;
	int m_calorieCount;

public:
	CatalogItem(const wxString& name, const wxBitmap& bmp, int calorieCount);

	// Getters + Setters
	const wxString& GetName() const { return m_name; }
	const wxBitmap& GetBmp() const { return m_itemBmp; }
	const int GetCalorieCount() const { return m_calorieCount; }

	void SetName(const wxString& name) { m_name = name; }
	void SetBmp(const wxBitmap& bmp) { m_itemBmp = bmp; }
	void SetCalorieCount(int count) { m_calorieCount = count; }
};

class FoodList: public wxListView
{
private:
	// Controls
	wxMenu* m_pMenu;
	wxImageList* m_pImageList;

	std::vector<CatalogItem>* m_pCatalogItems;

public:
	FoodList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_ICON);
	~FoodList();

	// Setup
	void Init();
	void SetupMenu();
	void SetupImageList();

	// Events
	void OnDoubleClickItem(wxListEvent& event);
	void OnRightClickItem(wxListEvent& event);
};

class NutritionCatalog: public wxFrame
{
private:
	FoodList* m_pFoodList;

	// Sizers
	wxBoxSizer* m_pTopSizer;

public:
	NutritionCatalog(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = NC_SIZE,
		long style = wxDEFAULT_FRAME_STYLE);

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events
};

#endif