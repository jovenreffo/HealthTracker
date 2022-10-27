#include "EntryList.h"
#include "StandardPath.hpp"

EntryList::EntryList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();
}

void EntryList::Init()
{
	this->SetupBitmaps();
	this->SetupList();
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