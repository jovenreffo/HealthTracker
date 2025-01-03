#ifndef NUTRITIONCATALOG_H
#define NUTRITIONCATALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <vector>

#include "CalorieList.h"

#define NC_SIZE (wxSize(640, 480))

class CatalogItem
{
private:
	// Information about the item
	wxString m_name;
	wxBitmap m_itemBmp;

	// Nutritional information
	int m_calories;
	int m_protein;
	int m_carbohydrates;
	int m_fiber;

	int m_quantity; // TODO: ADD TO CTOR

public:
	CatalogItem(const wxString& name, const wxBitmap& bmp, int calories, int protein, int carbohydrates, int fiber)
		: m_name{ name }, m_itemBmp{ bmp }, m_calories{ calories }, m_protein{ protein }, m_carbohydrates{ carbohydrates }, m_fiber{ fiber }
	{
	}

	// Getters
	const wxString& GetName() const { return m_name; }
	const wxBitmap& GetBmp() const { return m_itemBmp; }
	const int GetCalories() const { return m_calories; }
	const int GetProtein() const { return m_protein; }
	const int GetCarbohydrates() const { return m_carbohydrates; }
	const int GetFiber() const { return m_fiber; }
	const int GetQuantity() const { return m_quantity; }

	// Setters
	void SetName(const wxString& name) { m_name = name; }
	void SetBmp(const wxBitmap& bmp) { m_itemBmp = bmp; }
	void SetCalories(int count) { m_calories = count; }
	void SetProtein(int count) { m_protein = count; }
	void SetCarbohydrates(int count) { m_carbohydrates = count; }
	void SetFiber(int count) { m_fiber = count; }
	void SetQuantity(int count) { m_quantity = count; }
};

class ItemViewer; // defined in NutritionCatalog.cc

class FoodList: public wxListView
{
private:
	wxFrame* m_pFrame;

	// Controls
	wxMenu* m_pMenu;
	wxImageList* m_pImageList;
	ItemViewer* m_pItemViewer;

	// Information
	CalorieList* m_pCalorieList;
	std::vector<CatalogItem> m_catalogItems;

	// List vars
	long m_insertionIndex{ 0 };
	long m_bmpIndex{ 0 };
	long m_selectionIndex;
	wxString m_currentItemName;

public:
	FoodList(CalorieList* pCalorieList,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_ICON);
	~FoodList();

	ItemViewer* GetItemViewer() const { return m_pItemViewer; }

	// Setup
	void Init();
	void SetupMenu();
	void SetupImageList();
	void SetupDefaultNutritionItems();

	// Operations
	void AddImageToList(const wxBitmap& bmp) { m_pImageList->Add(bmp); }
	void AddNutritionItem(const CatalogItem& info);
	void OpenItem();

	// Events
	void OnSelectItem(wxListEvent& event);
	void OnDoubleClickItem(wxListEvent& event);
	void OnRightClickItem(wxListEvent& event);
	void OnOpenItem(wxCommandEvent& event);
};

class NutritionCatalog: public wxFrame
{
private:
	CalorieList* m_pCalorieList;
	FoodList* m_pFoodList;

	// Sizers
	wxBoxSizer* m_pTopSizer;

public:
	FoodList* GetFoodList() const { return m_pFoodList; }

public:
	NutritionCatalog(CalorieList* pCalorieList,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Nutrition Catalog"),
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