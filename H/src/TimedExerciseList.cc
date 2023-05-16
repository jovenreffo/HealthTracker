#include "TimedExerciseList.h"
#include "StandardPath.hpp"

TimedExerciseList::TimedExerciseList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();

	// Bind
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &TimedExerciseList::OnRightClickItem, this);
	m_pMenu->Bind(wxEVT_MENU, &TimedExerciseList::OnDeleteItem, this, wxID_DELETE);
}

TimedExerciseList::~TimedExerciseList()
{
	// Unbind
	this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &TimedExerciseList::OnRightClickItem, this);
	m_pMenu->Unbind(wxEVT_MENU, &TimedExerciseList::OnDeleteItem, this, wxID_DELETE);
}

void TimedExerciseList::AddItem(const TEL& tel)
{
	this->InsertItem(0, wxString(std::to_string(tel.m_hours)) << ':' << tel.m_mins << ':' << tel.m_secs);
	this->SetItem(0, 1, std::to_string(tel.m_distance));
	this->SetItem(0, 2, std::to_string(tel.m_cals));
}

void TimedExerciseList::Init()
{
	this->SetupMenu();
	this->SetupColumns();
	this->SetupImageList();
}

void TimedExerciseList::SetupMenu()
{
	m_pMenu = new wxMenu();

	m_pMenu->Append(wxID_DELETE, _T("&Delete"));
}

void TimedExerciseList::SetupColumns()
{
	this->AppendColumn(_T("Duration"));
	this->AppendColumn(_T("Distance (km)"), wxLIST_FORMAT_LEFT, 100); // wider label
	this->AppendColumn(_T("Calories"));
}

void TimedExerciseList::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_calorieBmp = wxBitmap(path_data::dataDir + _T("\\images\\calorie_small.png"), wxBITMAP_TYPE_PNG);
	m_pImageList->Add(m_calorieBmp);

	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void TimedExerciseList::OnSelectItem(wxListEvent& event)
{
	m_currentItemIndex = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}
	
void TimedExerciseList::OnRightClickItem(wxListEvent& event) 
{
	this->PopupMenu(m_pMenu);
}

void TimedExerciseList::OnDeleteItem(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
	{
		this->DeleteItem(m_currentItemIndex);
	}
}