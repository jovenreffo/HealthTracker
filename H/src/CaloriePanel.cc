#include "CaloriePanel.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(CaloriePanel, wxPanel)
	EVT_BUTTON(static_cast<int>(C::ID_NEW_ITEM), CaloriePanel::OnNewItem)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(CalorieList, wxListView)
	EVT_LIST_ITEM_RIGHT_CLICK(wxID_ANY, CalorieList::OnRightClick)
	EVT_LIST_ITEM_ACTIVATED(wxID_ANY, CalorieList::OnDoubleClick)
	EVT_MENU(wxID_DELETE, CalorieList::OnDeleteItem)
END_EVENT_TABLE()

CaloriePanel::CaloriePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void CaloriePanel::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void CaloriePanel::SetupListView()
{
	m_pListView->AppendColumn(_T("Food/Item"));
	m_pListView->AppendColumn(_T("Calories"));
	this->SetupImageList();
}

void CaloriePanel::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_calorieBmp = wxBitmap(path_data::dataDir + _T("\\Images\\calorie_small.png"), wxBITMAP_TYPE_PNG);
	m_calorieBmp.ResetAlpha();

	m_pImageList->Add(m_calorieBmp);
	m_pListView->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void CaloriePanel::SetupControls()
{
	m_pListView = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	this->SetupListView();

	m_pAddButton = new wxButton(this, static_cast<int>(C::ID_NEW_ITEM), _T("Add Item"), wxDefaultPosition, wxDefaultSize);
}

void CaloriePanel::SetupSizers()
{
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pBoxSizer);

	m_pBoxSizer->Add(m_pListView, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pBoxSizer->Add(m_pAddButton, wxSizerFlags().Proportion(0).Border(wxALL, 5));
}

// Events

void CaloriePanel::OnNewItem(wxCommandEvent& event)
{
	m_pAddItemDlg = new AddItemDlg(this, wxID_ANY, _T("Add Item"), wxDefaultPosition, wxDefaultSize);
	m_pAddItemDlg->Show(true);
}

// ======================== CalorieList class ========================

CalorieList::CalorieList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
}

void CalorieList::OnRightClick(wxListEvent& event)
{
}

void CalorieList::OnDoubleClick(wxListEvent& event)
{
}

void CalorieList::OnDeleteItem(wxCommandEvent& event)
{
}
