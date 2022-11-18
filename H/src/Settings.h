#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <wx/panel.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>

// SE, Settings Enum
enum class SE
{
	ID_RESET_ALL,
	ID_RESET_WORKOUTS,
	ID_RESET_ROUTINES
};

class Settings: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxStaticBoxSizer* m_pTopSizer;
	wxStaticBoxSizer* m_pResetBox;
	wxStaticBox* m_pTopParent;
	
	wxButton* m_pResetAll;
	wxButton* m_pResetWorkouts;
	wxButton* m_pResetRoutines;

public:
	Settings(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Panel/control setup
	void Init();
	void SetupControls();
	void SetupSizers();
	
	// Controls
	void AddAllControls();
	void AddResetGroup();

	// Events

};

#endif