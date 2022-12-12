#include "WorkoutDialog.h"

// Event table
BEGIN_EVENT_TABLE(WorkoutDialog, wxDialog)

END_EVENT_TABLE()

WorkoutDialog::WorkoutDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
}

void WorkoutDialog::Init()
{
	this->SetupImageList();
	this->SetupControls();
	this->SetupSizers();
	this->SetupWindowSizing();
}

void WorkoutDialog::SetupWindowSizing()
{
}

void WorkoutDialog::SetupImageList()
{
}

void WorkoutDialog::SetupControls()
{
}

void WorkoutDialog::SetupSizers()
{
}
