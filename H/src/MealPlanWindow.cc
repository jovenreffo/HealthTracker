#include "MealPlanWindow.h"

BEGIN_EVENT_TABLE(MealPlanWindow, wxFrame)

END_EVENT_TABLE()

MealPlanWindow::MealPlanWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
}

MealPlanWindow::~MealPlanWindow()
{

}
