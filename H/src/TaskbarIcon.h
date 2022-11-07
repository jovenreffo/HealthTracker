#ifndef _TASKBARICON_H_
#define _TASKBARICON_H_

#include <wx/taskbar.h>
#include <wx/menu.h>

enum class TBI
{
	ID_TBI_RESTORE,
	ID_TBI_EXIT
};

class TaskbarIcon: public wxTaskBarIcon
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pMenu;

public:
	TaskbarIcon();

	void SetupPopupMenu();

	// events
	void OnRightClick(wxTaskBarIconEvent& WXUNUSED(event));
	void OnDoubleClick(wxTaskBarIconEvent& WXUNUSED(event));
	void OnRestore(wxCommandEvent& WXUNUSED(event));
	void OnExit(wxCommandEvent& WXUNUSED(event));
};

#endif