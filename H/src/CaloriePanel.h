#ifndef _CALORIEPANEL_H_
#define _CALORIEPANEL_H_

#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/imaglist.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/bmpbuttn.h>

#include "AddItemDlg/AddItemDlg.h"
#include "NutritionCatalogHTML/NutritionCatalog.h"

enum class CP
{
	ID_SEARCH,
	ID_NEW_ITEM,
	ID_TOTAL
};

class CalorieList;

class CaloriePanel: public wxPanel
{
private:
	wxBoxSizer* m_pBoxSizer;
	CalorieList* m_pCalorieList;

	AddItemDlg* m_pAddItemDlg;
	NutritionCatalog* m_pNutritionCatalog;

	wxBitmapButton* m_pSearchButton;
	wxBitmapButton* m_pAddButton;
	wxBitmapButton* m_pSaveButton;
	wxBitmap m_searchBmp;
	wxBitmap m_addBmp;
	wxBitmap m_saveBmp;
	
public:
	CaloriePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~CaloriePanel();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();

	void AddNewItem();

	// Events
	void OnSearch(wxCommandEvent& event);
	void OnNewItem(wxCommandEvent& event);
	void OnSaveInformation(wxCommandEvent& event);
};

class CalorieList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pMenu;
	wxImageList* m_pImageList;
	wxBitmap m_calorieBmp;
	CaloriePanel* m_pCaloriePanel;

	Total m_total;

public:
	CalorieList(CaloriePanel* pCaloriePanel,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);
	~CalorieList();

	Total GetTotal() const { return m_total; }
	void AddItem(const wxString& item, AddItemDlg* pAddItemDlg);
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