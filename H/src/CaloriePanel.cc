#include "CaloriePanel.h"

BEGIN_EVENT_TABLE(CaloriePanel, wxPanel)
	EVT_BUTTON(static_cast<int>(CAL::ID_NEW_ITEM), CaloriePanel::OnNewItem)
END_EVENT_TABLE()

CaloriePanel::CaloriePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
}


// Events

void CaloriePanel::OnNewItem(wxCommandEvent& event)
{

}