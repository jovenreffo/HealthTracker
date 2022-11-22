#include "RoutineView.h"

BEGIN_EVENT_TABLE(RoutineView, wxDialog)


END_EVENT_TABLE()

RoutineView::RoutineView(const std::vector<Routine>& routineInfo, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_routineInfo{ routineInfo }
{
	this->Init();
}

void RoutineView::Init()
{
	this->SetupControls();
	this->CreateControls();
	this->SetupSizing();
}

void RoutineView::SetupSizing()
{
	this->SetMinSize(RVDLG_SIZE);
	this->SetMaxSize(RVDLG_MAX_SIZE);
	this->SetInitialSize(RVDLG_SIZE);
}

void RoutineView::SetupControls()
{
}

void RoutineView::CreateControls()
{
}

void RoutineView::OnOK(wxCommandEvent& event)
{
}

void RoutineView::OnEnter(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_OK);
	this->Show(false);
}

void RoutineView::OnClose(wxCloseEvent& event)
{
	this->Destroy();
}
