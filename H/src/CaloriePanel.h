#ifndef _CALORIEPANEL_H_
#define _CALORIEPANEL_H_

#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>

enum class C
{
	ID_NEW_ITEM
};

class CaloriePanel: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxBoxSizer* m_pBoxSizer;
	wxListView* m_pListView;
	wxButton* m_pAddButton;

public:
	CaloriePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Setup
	void Init();
	void SetupListView();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnNewItem(wxCommandEvent& event);
};

#endif