#include "CaloriePanel.h"

BEGIN_EVENT_TABLE(CaloriePanel, wxPanel)
	EVT_BUTTON(static_cast<int>(C::ID_NEW_ITEM), CaloriePanel::OnNewItem)
END_EVENT_TABLE()

CaloriePanel::CaloriePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void CaloriePanel::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void CaloriePanel::SetupControls()
{
}

void CaloriePanel::SetupSizers()
{
}

// Events

void CaloriePanel::OnNewItem(wxCommandEvent& event)
{

}