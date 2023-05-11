#include "TimedExerciseList.h"

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

}

void TimedExerciseList::SetupColumns()
{

}

void TimedExerciseList::SetupImageList()
{

}