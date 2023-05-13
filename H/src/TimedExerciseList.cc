#include "TimedExerciseList.h"
#include "StandardPath.hpp"

TimedExerciseList::TimedExerciseList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();
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
	this->AppendColumn(_T("Distance (km)"));
	this->AppendColumn(_T("Calories"));
}

void TimedExerciseList::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_calorieBmp = wxBitmap(path_data::dataDir + _T("\\images\\calorie_small.bmp"));
	m_pImageList->Add(m_calorieBmp);

	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}