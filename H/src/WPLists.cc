#include <wx/msgdlg.h>
#include <wx/config.h>
#include "WPLists.h"
#include "StandardPath.hpp"
#include "WorkoutWindow.h" // A circular dependency will occur if this is put in WPLists.h

// event table for WorkoutList
BEGIN_EVENT_TABLE(WorkoutList, wxListView)
	EVT_LIST_ITEM_RIGHT_CLICK(wxID_ANY, WorkoutList::OnRightClick)
	EVT_LIST_ITEM_ACTIVATED(wxID_ANY, WorkoutList::OnDoubleClick)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, WorkoutList::OnItemSelected)
	EVT_MENU(wxID_OPEN, WorkoutList::OnOpen)
	EVT_MENU(wxID_DELETE, WorkoutList::OnDelete)
END_EVENT_TABLE()

// event table for RoutineList
BEGIN_EVENT_TABLE(RoutineList, wxListView)
	EVT_LIST_ITEM_RIGHT_CLICK(wxID_ANY, RoutineList::OnRightClick)
	EVT_LIST_ITEM_ACTIVATED(wxID_ANY, RoutineList::OnDoubleClick)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, RoutineList::OnItemSelected)
	EVT_MENU(wxID_OPEN, RoutineList::OnOpen)
	EVT_MENU(wxID_DELETE, RoutineList::OnDelete)
END_EVENT_TABLE()

WorkoutList::WorkoutList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView{ parent, id, pos, size, style }
{
	this->Init();
}

WorkoutList::~WorkoutList()
{
	this->SaveToConfig();
}

void WorkoutList::Init()
{
	this->SetupImageList();
	this->SetupColumn();
	this->SetupMenu();

	this->LoadFromConfig();
}

void WorkoutList::LoadFromConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/WPLists/"));
	m_numEntries = pConfig->Read(_T("NumEntries"), 0L);
	
	// Load entry content before names so the items can be added
	wxArrayString entryContentArr;
	pConfig->SetPath(_T("/WPLists/WorkoutContent"));
	for (auto i{ m_numEntries - 1 }; i >= 0; --i) // reverse order because of how the entries are saved to the config file
	{
		wxString curr;

		if (pConfig->Read(std::to_string(i), &curr))
			entryContentArr.Add(curr);
	}

	// load the entry names and add items to the list
	pConfig->SetPath(_T("/WPLists/WorkoutNames"));

	for (auto i{ m_numEntries - 1 }; i >= 0; --i)
	{
		wxString curr;

		if (pConfig->Read(std::to_string(i), &curr))
			this->AddItem(curr, entryContentArr[i]);
	}
}

void WorkoutList::SaveToConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/WPLists/"));
	// save the number of entries
	m_numEntries = this->GetItemCount(); // read the number of entries into the variable
	pConfig->Write(_T("NumEntries"), m_numEntries); // then save it to the config
	
	// save workout names
	pConfig->SetPath(_T("/WPLists/WorkoutNames"));
	for (auto i{ 0 }; i < this->GetItemCount(); ++i)
	{
		pConfig->Write(std::to_string(i), this->GetItemText(i));
	}

	// save workout content
	pConfig->SetPath(_T("/WPLists/WorkoutContent"));
	for (auto i{ 0 }; i < this->GetItemCount(); ++i)
	{
		// Recieve content associated at index 'i'
		pConfig->Write(std::to_string(i), this->GetContent()[i].GetContent());
	}
}

void WorkoutList::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_workoutBmp = wxBitmap(path_data::dataDir + _T("\\Images\\workout_small.png"), wxBITMAP_TYPE_PNG);
	m_workoutBmp.ResetAlpha();

	m_pImageList->Add(m_workoutBmp);
	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void WorkoutList::SetupColumn()
{
	wxListItem workoutCol;
	workoutCol.SetText(_T("Workouts"));
	workoutCol.SetImage(-1);
	this->InsertColumn(0, workoutCol);
	this->SetColumnWidth(0, 200);
}

void WorkoutList::SetupMenu()
{
	m_pMenu = new wxMenu();
	m_pMenu->Append(wxID_OPEN, _T("Open Workout"));
	m_pMenu->AppendSeparator();
	m_pMenu->Append(wxID_DELETE, _T("Delete"));
}

void WorkoutList::AddItem(const wxString& name, const wxString& content)
{
	// insert an item at index 0, add a name-content pair to the content container
	this->InsertItem(0, name);
	m_content.push_back({ name, content });
}

void WorkoutList::ResetList()
{
	this->DeleteAllItems();
}

void WorkoutList::OpenWorkout()
{
	WorkoutWindow* pWorkoutDlg = new WorkoutWindow(this, this, wxID_ANY);

	// search the content array to see if an item exists with the currently selected name
	try
	{
		for (auto i{ 0 }; i < m_content.size(); ++i)
		{
			if (m_currentItemName == m_content[i].GetName())
			{
				pWorkoutDlg->OpenWorkout(m_content[i].GetContent());
				pWorkoutDlg->SetTitle(wxString(_T("View Workout - ")) << m_currentItemName);
			}
		}
	}
	catch (std::exception& e)
	{
		wxLogMessage(_T("No item with that name exists.\n%s"), e.what());
	}
}

void WorkoutList::OpenWorkout(const wxString& name)
{
	WorkoutWindow* pWorkoutWindow = new WorkoutWindow(this, this, wxID_ANY, wxString(_T("View Workout - ")) << name);
	pWorkoutWindow->Show(true);

	for (auto i{ 0 }; i < m_content.size(); ++i)
	{
		if (name == m_content[i].GetName())
			pWorkoutWindow->OpenWorkout(m_content[i].GetContent());
	}
}

// Events

void WorkoutList::OnRightClick(wxListEvent& event)
{
	this->PopupMenu(m_pMenu);
}

void WorkoutList::OnDoubleClick(wxListEvent& event)
{
	this->OpenWorkout();
}

void WorkoutList::OnItemSelected(wxListEvent& event)
{
	m_selectionIndex = this->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	m_currentItemName = this->GetItemText(m_selectionIndex);
}

void WorkoutList::OnOpen(wxCommandEvent& event)
{
	this->OpenWorkout();
}

void WorkoutList::OnDelete(wxCommandEvent& event)
{
	// make sure the user wants to delete the selected item
	if (wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		this->DeleteItem(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
}

// ====== RoutineList ======

RoutineList::RoutineList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView{ parent, id, pos, size, style }
{
	this->Init();
}

void RoutineList::Init()
{
	this->SetupColumn();
	this->SetupImageList();
	this->SetupMenu();
}

void RoutineList::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_routineBmp = wxBitmap(path_data::dataDir + _T("\\Images\\routine.png"), wxBITMAP_TYPE_PNG);
	m_routineBmp.ResetAlpha();

	m_pImageList->Add(m_routineBmp);
	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void RoutineList::SetupColumn()
{
	wxListItem workoutCol;
	workoutCol.SetText(_T("Routines"));
	workoutCol.SetImage(-1);
	this->InsertColumn(0, workoutCol);
	this->SetColumnWidth(0, 200);
}

void RoutineList::SetupMenu()
{
	m_pMenu = new wxMenu();

	m_pMenu->Append(wxID_OPEN, _T("&Open Routine"));
	m_pMenu->AppendSeparator();
	m_pMenu->Append(wxID_DELETE, _T("&Delete"));
}

void RoutineList::AddItem(const wxString& name, const Routine& routine)
{
	m_routineInfo.push_back(routine);
	this->InsertItem(m_insertionIndex, name);
	++m_insertionIndex;
}

void RoutineList::ResetList()
{
	this->DeleteAllItems();
}

void RoutineList::OpenRoutine()
{
	if (!m_content.empty())
	{
		m_pRoutineView = new RoutineView(m_selectionIndex, m_routineInfo[m_selectionIndex], m_content, this, wxID_ANY, wxString(_T("View Routine - ")) << m_currentItemName, wxDefaultPosition);
		m_pRoutineView->Show(true);

		if (m_pRoutineView->ShowModal() == wxID_OK)
		{

		}
	}
}

void RoutineList::OnRightClick(wxListEvent& event)
{
	this->PopupMenu(m_pMenu);
}

void RoutineList::OnDoubleClick(wxListEvent& event)
{
	this->OpenRoutine();
}

void RoutineList::OnItemSelected(wxListEvent& event)
{
	m_selectionIndex = this->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	m_currentItemName = this->GetItemText(m_selectionIndex);
}

void RoutineList::OnOpen(wxCommandEvent& event)
{
	this->OpenRoutine();
}

void RoutineList::OnDelete(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		this->DeleteItem(m_selectionIndex);
}
