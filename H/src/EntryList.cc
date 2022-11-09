#include <wx/msgdlg.h>
#include "EntryList.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(EntryList, wxListView)
	EVT_LIST_ITEM_RIGHT_CLICK(wxID_ANY, EntryList::OnRightClick)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, EntryList::OnItemSelected)
	EVT_MENU(wxID_DELETE, EntryList::OnRemoveEntry)
	EVT_MENU(wxID_OPEN, EntryList::OnOpenEntry)
END_EVENT_TABLE()

EntryList::EntryList(wxTextCtrl* pTextCtrl, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style), m_pTextCtrl{ pTextCtrl }
{
	this->Init();
}

void EntryList::AddItem(const wxString& name, const wxString& content)
{
	this->InsertItem(0, name);

}

void EntryList::Init()
{
	this->SetupPopUpMenu();
	this->SetupBitmaps();
	this->SetupList();
}

void EntryList::SetupPopUpMenu()
{
	m_pPopUpMenu = new wxMenu;

	m_pPopUpMenu->Append(wxID_OPEN, _T("Open Entry\tCtrl+O"));
	m_pPopUpMenu->AppendSeparator();
	m_pPopUpMenu->Append(wxID_DELETE, _T("&Delete"));
}

void EntryList::SetupBitmaps()
{
	m_pencilBmp = wxBitmap(path_data::dataDir + _T("\\Images\\pencil.png"), wxBITMAP_TYPE_PNG);

	m_pImageList = new wxImageList(16, 16);
	m_pImageList->Add(m_pencilBmp);
	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void EntryList::SetupList()
{
	m_itemCol.SetText(_T("Entries"));
	m_itemCol.SetImage(-1);
	this->InsertColumn(0, m_itemCol);
	this->SetColumnWidth(0, 500);
}

// Events

void EntryList::OnRightClick(wxListEvent& event)
{
	this->PopupMenu(m_pPopUpMenu);
}

void EntryList::OnItemSelected(wxListEvent& event)
{
	m_selectionIndex = this->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	m_currentItemName = this->GetItemText(m_selectionIndex);
}

void EntryList::OnOpenEntry(wxCommandEvent& event)
{

}

void EntryList::OnRemoveEntry(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_WARNING) == wxYES)
		this->DeleteItem(m_selectionIndex);
}
