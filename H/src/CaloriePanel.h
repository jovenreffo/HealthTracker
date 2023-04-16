#ifndef _CALORIEPANEL_H_
#define _CALORIEPANEL_H_

#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/imaglist.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/bmpbuttn.h>

#include "AddItemDlg.h"
#include "NutritionCatalog.h"
#include "CalorieList.h"

enum class CP
{
	ID_SEARCH,
	ID_NEW_ITEM,
	ID_TOTAL
};

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

#endif