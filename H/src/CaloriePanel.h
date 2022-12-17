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

enum class CP
{
	ID_NEW_ITEM,
	ID_TOTAL
};

class CalorieList;

class CaloriePanel: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxBoxSizer* m_pBoxSizer;
	CalorieList* m_pCalorieList;
	wxBitmapButton* m_pAddButton;
	wxBitmap m_addBmp;

	AddItemDlg* m_pAddItemDlg;


public:
	CaloriePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();

	void AddNewItem();

	// Events
	void OnNewItem(wxCommandEvent& event);
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

	void AddItem(const wxString& item, AddItemDlg* pAddItemDlg);
	void UpdateTotal();

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
};

#endif