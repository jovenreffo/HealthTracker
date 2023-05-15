#include "TimedExerciseList.h"
#include "StandardPath.hpp"

TimedExerciseList::TimedExerciseList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();
}

void TimedExerciseList::AddItem(const TEL& tel)
{
	this->InsertItem(0, wxString(std::to_string(tel.m_hours)) << ':' << tel.m_mins << ':' << tel.m_secs);
	this->SetItem(0, 1, std::to_string(tel.m_distance));
	this->SetItem(0, 1, std::to_string(tel.m_cals));
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