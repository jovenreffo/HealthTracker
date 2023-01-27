#ifndef _TASKBARICON_H_
#define _TASKBARICON_H_

#include <wx/taskbar.h>
#include <wx/frame.h>
#include <wx/menu.h>

#include "AboutDialog/AboutDialog.h"

enum class TBI
{
	ID_TBI_RESTORE,
	ID_TBI_EXIT,
	ID_TBI_FULLSCREEN
};

class TaskbarIcon: public wxTaskBarIcon
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pMenu;
	wxFrame* m_pParent;
	AboutDialog* m_pAboutDialog;

public:
	TaskbarIcon(wxFrame* parent);

	void SetupPopupMenu();

	// events
	void OnRightClick(wxTaskBarIconEvent& WXUNUSED(event));
	void OnDoubleClick(wxTaskBarIconEvent& WXUNUSED(event));
	void OnAbout(wxCommandEvent& WXUNUSED(event));
	void OnMaximize(wxCommandEvent& WXUNUSED(event));
	void OnExit(wxCommandEvent& WXUNUSED(event));
};

#endif