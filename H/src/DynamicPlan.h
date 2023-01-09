#ifndef DYNAMICPLAN_H
#define DYNAMICPLAN_H

#include <wx/panel.h>
#include <wx/button.h>
#include "aui_includes/aui_includes.h"

// Define a class that inherits from wxPanel, is a certain-sized, rectangle, and holds exercise information for tracking on the fly

class DynamicPlan : public wxPanel
{
private:
	wxAuiManager m_auiMgr;

public:
	DynamicPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif