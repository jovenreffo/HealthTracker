#ifndef _CALORIEPANEL_H_
#define _CALORIEPANEL_H_

#include <wx/panel.h>
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/imaglist.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/bmpbuttn.h>
#include <wx/html/htmlwin.h>

#include "AddItemDlg.h"
#include "NutritionCatalog.h"
#include "CalorieList.h"
#include "Nutrient Total/Total.hpp"

// ===== ToolsWindow =====

#define TW_SIZE (wxSize(465, 440))

class ToolsWindow: public wxDialog
{
private:
	// Controls and necessary members
	wxHtmlWindow* m_pHtmlWin;
	wxButton* m_pOk;

	// Sizer
	wxBoxSizer* m_pTopSizer;

public:
	ToolsWindow(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Nutrition Tools"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = TW_SIZE,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~ToolsWindow();

	// Setup
	void InitToolsWindow();
	void SetupHTMLWindow();
	void SetupButtons();
	void SetupSizers();
	void SetupSizing();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnLinkClicked(wxHtmlLinkEvent& event);
};

// ===== CPanelSettings =====

enum class CPS
{
	ID_VIEW_TOOLS
};

class CPanelSettings: public wxDialog
{
private:
	// Controls
	wxSpinCtrl* m_pCalorieGoal;
	wxSpinCtrl* m_pProteinGoal;
	wxButton* m_pViewTools;
	wxButton* m_pOk;
	wxButton* m_pCancel;
	ToolsWindow* m_pToolsWindow;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pControlSizer;
	
	// Validator
	int m_calorieGoal;
	int m_proteinGoal;

public:
	CPanelSettings(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Nutrition Settings"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~CPanelSettings();

	// Getters
	const int GetCalorieGoal() const { return m_calorieGoal; }
	const int GetProteinGoal() const { return m_proteinGoal; }

	// Setters for ctrls
	void SetCalorieCtrl(int val);
	void SetProteinCtrl(int val);

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnViewTools(wxCommandEvent& event);
};

// ===== CaloriePanel =====

enum class CP
{
	ID_SEARCH,
	ID_NEW_ITEM,
	ID_TOTAL,
	ID_SETTINGS
};

class CaloriePanel: public wxPanel
{
private:
	wxBoxSizer* m_pBoxSizer;
	CalorieList* m_pCalorieList;

	AddItemDlg* m_pAddItemDlg;
	NutritionCatalog* m_pNutritionCatalog;
	CPanelSettings* m_pPanelSettings;

	wxBitmapButton* m_pSearchButton;
	wxBitmapButton* m_pAddButton;
	wxBitmapButton* m_pSaveButton;
	wxBitmapButton* m_pSettingsButton;
	wxBitmap m_searchBmp;
	wxBitmap m_addBmp;
	wxBitmap m_saveBmp;
	wxBitmap m_settingsBmp;

	// vars for config
	int m_calorieGoal;
	int m_proteinGoal;
	
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
	void SaveConfig();
	void LoadConfig();

	void AddNewItem();

	// Events
	void OnSearch(wxCommandEvent& event);
	void OnNewItem(wxCommandEvent& event);
	void OnSaveInformation(wxCommandEvent& event);
	void OnOpenSettings(wxCommandEvent& event);
};

#endif