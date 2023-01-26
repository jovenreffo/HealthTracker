#include <wx/msgdlg.h>
#include "TaskbarIcon.h"

// event table
BEGIN_EVENT_TABLE(TaskbarIcon, wxTaskBarIcon)
	EVT_TASKBAR_LEFT_DCLICK(TaskbarIcon::OnDoubleClick)
	EVT_TASKBAR_CLICK(TaskbarIcon::OnRightClick)
	EVT_MENU(wxID_ABOUT, TaskbarIcon::OnAbout)
	EVT_MENU((int)TBI::ID_TBI_EXIT, TaskbarIcon::OnExit)
	EVT_MENU((int)TBI::ID_TBI_FULLSCREEN, TaskbarIcon::OnMaximize)
END_EVENT_TABLE()

TaskbarIcon::TaskbarIcon(wxFrame* parent)
	: wxTaskBarIcon{}, m_pParent{ parent }
{
	this->SetupPopupMenu();
}

void TaskbarIcon::SetupPopupMenu()
{
	m_pMenu = new wxMenu();

	m_pMenu->Append(wxID_ABOUT, _T("&About"));
	m_pMenu->Append((int)TBI::ID_TBI_FULLSCREEN, _T("Maximize"));
	m_pMenu->AppendSeparator();
	m_pMenu->Append((int)TBI::ID_TBI_EXIT, _T("&Exit"));
}

void TaskbarIcon::OnRightClick(wxTaskBarIconEvent& WXUNUSED(event))
{
	this->PopupMenu(m_pMenu);
}

void TaskbarIcon::OnDoubleClick(wxTaskBarIconEvent& WXUNUSED(event))
{

}

void TaskbarIcon::OnAbout(wxCommandEvent& WXUNUSED(event))
{

}

void TaskbarIcon::OnMaximize(wxCommandEvent& WXUNUSED)
{
	m_pParent->ShowFullScreen(true, wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
}

void TaskbarIcon::OnExit(wxCommandEvent& WXUNUSED(event))
{
	if (wxMessageBox(_T("Are you sure you want to quit?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		m_pParent->Destroy();
}
