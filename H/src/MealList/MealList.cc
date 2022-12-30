#include <wx/stdpaths.h>
#include "MealList.h"

MealList::MealList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();

	// Bind events
	m_pMenu->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MealList::OnItemRightClick, this);
	m_pColMenu->Bind(wxEVT_LIST_COL_RIGHT_CLICK, &MealList::OnColumnRightClick, this);
}

MealList::~MealList()
{
	// Unbind events
	m_pMenu->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MealList::OnItemRightClick, this);
	m_pColMenu->Unbind(wxEVT_LIST_COL_RIGHT_CLICK, &MealList::OnColumnRightClick, this);
}

void MealList::Init()
{
	this->SetupImageList();
	this->SetupColumn();
	this->SetupMenu();
}

void MealList::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_mealBmp = wxBitmap(wxStandardPaths::Get().GetDataDir() + _T("\\Images\\meal_plan_small.png"), wxBITMAP_TYPE_PNG);
	m_mealBmp.ResetAlpha();

	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void MealList::SetupColumn()
{
	wxListItem col;
	col.SetText(_T("Meal Plans"));
	col.SetImage(-1);
	this->InsertColumn(0, col);
	this->SetColumnWidth(0, 200);
}

void MealList::SetupMenu()
{
	// Menu for right-clicking items
	m_pMenu = new wxMenu();

	m_pMenu->AppendSeparator();
	m_pMenu->Append(wxID_DELETE, _T("&Delete"));

	// Menu for right-clicking columns
	m_pColMenu = new wxMenu();
}

void MealList::OnItemRightClick(wxListEvent& event)
{

}

void MealList::OnColumnRightClick(wxListEvent& event)
{

}