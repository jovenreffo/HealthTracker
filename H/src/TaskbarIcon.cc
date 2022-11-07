#include "TaskbarIcon.h"

// event table
BEGIN_EVENT_TABLE(TaskbarIcon, wxTaskBarIcon)
	EVT_TASKBAR_LEFT_DCLICK(TaskbarIcon::OnDoubleClick)
	EVT_TASKBAR_CLICK(TaskbarIcon::OnRightClick)
	EVT_MENU((int)TBI::ID_TBI_RESTORE, TaskbarIcon::OnRestore)
	EVT_MENU((int)TBI::ID_TBI_EXIT, TaskbarIcon::OnExit)
END_EVENT_TABLE()

TaskbarIcon::TaskbarIcon()
	: wxTaskBarIcon{}
{
	this->SetupPopupMenu();
}

void TaskbarIcon::SetupPopupMenu()
{
	m_pMenu = new wxMenu();

	m_pMenu->AppendSeparator();
	m_pMenu->Append(static_cast<int>(TBI::ID_TBI_EXIT), _T("&Exit"));
}

void TaskbarIcon::OnRightClick(wxTaskBarIconEvent& WXUNUSED)
{
	this->PopupMenu(m_pMenu);
}

void TaskbarIcon::OnDoubleClick(wxTaskBarIconEvent& WXUNUSED)
{

}

void TaskbarIcon::OnRestore(wxCommandEvent& WXUNUSED)
{
}

void TaskbarIcon::OnExit(wxCommandEvent& WXUNUSED)
{
	this->Destroy();
}
