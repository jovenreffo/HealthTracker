#include <wx/stdpaths.h>
#include <wx/msgdlg.h>
#include "MealList.h"

MealList::MealList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();

	// Bind events
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MealList::OnItemRightClick, this);
	this->Bind(wxEVT_LIST_COL_RIGHT_CLICK, &MealList::OnColumnRightClick, this);
	m_pMenu->Bind(wxEVT_MENU, &MealList::OnDeleteItem, this, wxID_DELETE);
}

MealList::~MealList()
{
	// Unbind events
	this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MealList::OnItemRightClick, this);
	this->Unbind(wxEVT_LIST_COL_RIGHT_CLICK, &MealList::OnColumnRightClick, this);
	m_pMenu->Unbind(wxEVT_MENU, &MealList::OnDeleteItem, this, wxID_DELETE);
}

void MealList::AddItem(const wxString& name)
{
	this->InsertItem(0, name, 0);
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

	m_pImageList->Add(m_mealBmp);
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
	this->PopupMenu(m_pMenu);
}

void MealList::OnColumnRightClick(wxListEvent& event)
{

}

void MealList::OnDeleteItem(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		this->DeleteItem(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
}