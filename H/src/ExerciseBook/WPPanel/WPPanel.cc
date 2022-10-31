#include "WPPanel.h"

BEGIN_EVENT_TABLE(WPPanel, wxPanel)

END_EVENT_TABLE()

WPPanel::WPPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
}
