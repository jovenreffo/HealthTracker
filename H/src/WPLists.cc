#include <wx/msgdlg.h>
#include "WPLists.h"

// event table for WorkoutList
BEGIN_EVENT_TABLE(WorkoutList, wxListView)
	EVT_LIST_ITEM_RIGHT_CLICK(wxID_ANY, WorkoutList::OnRightClick)
	EVT_LIST_ITEM_ACTIVATED(wxID_ANY, WorkoutList::OnDoubleClick)
	EVT_MENU(wxID_OPEN, WorkoutList::OnOpen)
	EVT_MENU(wxID_DELETE, WorkoutList::OnDelete)
END_EVENT_TABLE()

// event table for RoutineList
BEGIN_EVENT_TABLE(RoutineList, wxListView)

END_EVENT_TABLE()

WorkoutList::WorkoutList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView{ parent, id, pos, size, style }
{
	this->SetupColumn();
	this->SetupMenu();
}

void WorkoutList::SetupColumn()
{
	wxListItem routineCol;
	routineCol.SetText(_T("Workouts"));
	routineCol.SetImage(-1); 
	this->InsertColumn(0, routineCol);
	this->SetColumnWidth(0, 200);
}

void WorkoutList::SetupMenu()
{
	m_pMenu = new wxMenu();
	m_pMenu->Append(wxID_OPEN, _T("Open Workout\tCtrl+O"));
	m_pMenu->AppendSeparator();
	m_pMenu->Append(wxID_DELETE, _T("Delete"));
}

void WorkoutList::OnRightClick(wxListEvent& event)
{
	this->PopupMenu(m_pMenu);
}

void WorkoutList::OnDoubleClick(wxListEvent& event)
{

}

void WorkoutList::OnOpen(wxCommandEvent& event)
{

}

void WorkoutList::OnDelete(wxCommandEvent& event)
{
	// make sure the user wants to delete the selected item
	if(wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		this->DeleteItem(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
}

// ====== RoutineList ======

RoutineList::RoutineList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView{ parent, id, pos, size, style }
{
	this->SetupColumn();
}

void RoutineList::SetupColumn()
{
	wxListItem workoutCol;
	workoutCol.SetText(_T("Routines"));
	workoutCol.SetImage(-1);
	this->InsertColumn(0, workoutCol);
	this->SetColumnWidth(0, 200);
}
