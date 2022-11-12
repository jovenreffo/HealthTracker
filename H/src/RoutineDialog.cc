#include "RoutineDialog.h"

BEGIN_EVENT_TABLE(RoutineDialog, wxDialog)
	EVT_BUTTON(wxID_OK, RoutineDialog::OnOK)
	EVT_CLOSE(RoutineDialog::OnClose)
END_EVENT_TABLE()

RoutineDialog::RoutineDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog{ parent, id, title, pos, size, style }
{
	this->Init();
}

void RoutineDialog::Init()
{
	this->SetupControls();
	this->CreateControls();
}

void RoutineDialog::SetupControls()
{
}

void RoutineDialog::CreateControls()
{
}

// events

void RoutineDialog::OnOK(wxCommandEvent& WXUNUSED(event))
{
}

void RoutineDialog::OnClose(wxCloseEvent& WXUNUSED(event))
{
	this->Destroy();
}
