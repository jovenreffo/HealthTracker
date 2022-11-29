#ifndef _ADDITEMDLG_H_
#define _ADDITEMDLG_H_

// Dialog for adding an item to the calorie tracker

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#define ADDITEMDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )
#define ADDITEMDLG_SIZE  ( wxSize(400, 260) )
#define ADDITEMDLG_MAX	 ( wxSize(450, 280) )

enum class AID
{
	ID_CALORIE_TEXT,
	ID_CALORIE_SPIN,
	ID_CARB_SPIN,
	ID_PROTEIN_SPIN,
	ID_FIBER_SPIN
};

class AddItemDlg: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxTextCtrl* m_pFoodName;
	wxSpinCtrl* m_pCalories;
	wxSpinCtrl* m_pCarbCtrl;
	wxSpinCtrl* m_pProteinCtrl;
	wxSpinCtrl* m_pFiberCtrl;

	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pItemSizer;
	wxBoxSizer* m_pButtonSizer;

	wxString m_itemName;
	int m_calorieContent;
	int m_carbContent;
	int m_proteinContent;
	int m_fiberContent;

public:
	AddItemDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = ADDITEMDLG_STYLE);


	// Getters
	const wxString& GetItemName() const { return m_itemName; }
	const int GetCalorieContent() const { return m_calorieContent; }
	const int GetCarbContent() const { return m_carbContent; }
	const int GetProteinContent() const { return m_proteinContent; }
	const int GetFiberContent() const { return m_fiberContent; }

	// Setup
	void Init();
	void SetupSizing();
	void SetupControls();
	void SetupSizers();

	void HandleExit();

	// Events
	void OnUpdateOK(wxUpdateUIEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnSpinUp(wxSpinEvent& event);
};

#endif