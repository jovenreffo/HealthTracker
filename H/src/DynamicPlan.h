#ifndef _DYNAMICPLAN_H_
#define _DYNAMICPLAN_H_

#include <wx/panel.h>

class DynamicPlan : public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:

public:
	DynamicPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif