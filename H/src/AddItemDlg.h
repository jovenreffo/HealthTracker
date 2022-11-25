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
#define ADDITEMDLG_SIZE  ( wxSize(300, 225) )
#define ADDITEMDLG_MAX	 ( wxSize(350, 275) )

class AddItemDlg: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxTextCtrl* m_pFoodName;
	wxSpinCtrl* m_pCalories;

	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pItemSizer;
	wxBoxSizer* m_pButtonSizer;

	wxString m_itemName;
	int m_calorieContent;

public:
	AddItemDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = ADDITEMDLG_STYLE);

	const wxString& GetItemName() const { return m_itemName; }
	const int GetCalorieContent() const { return m_calorieContent; }

	// Setup
	void Init();
	void SetupSizing();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

#endif