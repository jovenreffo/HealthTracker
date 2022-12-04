#include <wx/msgdlg.h>
#include <wx/string.h>
#include "CaloriePanel.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"

// CaloriePanel event table
BEGIN_EVENT_TABLE(CaloriePanel, wxPanel)
	EVT_BUTTON(static_cast<int>(CP::ID_NEW_ITEM), CaloriePanel::OnNewItem)
END_EVENT_TABLE()

// CalorieList event table
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

void CaloriePanel::SetupControls()
{
	m_pCalorieList = new CalorieList(this, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	m_pAddButton = new wxButton(this, static_cast<int>(CP::ID_NEW_ITEM), _T("Add Item"), wxDefaultPosition, wxDefaultSize);
}

void CaloriePanel::SetupSizers()
{
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pBoxSizer);

	wxBoxSizer* m_pHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pHorizontalSizer->Add(m_pAddButton, wxSizerFlags().Proportion(0).Border(wxALL, 5));

	m_pBoxSizer->Add(m_pCalorieList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pBoxSizer->Add(m_pHorizontalSizer);
}

// Events

void CaloriePanel::OnNewItem(wxCommandEvent& event)
{
	m_pAddItemDlg = new AddItemDlg(this, wxID_ANY, _T("Add Item"), wxDefaultPosition, wxDefaultSize);
	m_pAddItemDlg->Show(true);

	if (m_pAddItemDlg->ShowModal() == wxID_OK)
	{
		m_pCalorieList->AddItem(m_pAddItemDlg->GetItemName(), m_pAddItemDlg);
		m_pCalorieList->UpdateTotal();
	}
}

// ======================== CalorieList class ========================

CalorieList::CalorieList(CaloriePanel* pCaloriePanel, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style), m_pCaloriePanel{ pCaloriePanel }
{
	this->Init();
}

void CalorieList::AddItem(const wxString& item, AddItemDlg* pAddItemDlg)
{
	this->InsertItem(1, item);
	this->SetItem(1, 1, std::to_string(pAddItemDlg->GetCalorieContent()));
	this->SetItem(1, 2, std::to_string(pAddItemDlg->GetCarbContent()));
	this->SetItem(1, 3, std::to_string(pAddItemDlg->GetProteinContent()));
	this->SetItem(1, 4, std::to_string(pAddItemDlg->GetFiberContent()));
}

void CalorieList::UpdateTotal()
{
	m_total.ResetTotal();
	// begin at 1 so we don't include the total
	for (auto i{ 1 }; i < this->GetItemCount(); ++i)
	{
		m_total.m_calTotal += wxAtoi(this->GetItemText(i, 1));
		m_total.m_carbTotal += wxAtoi(this->GetItemText(i, 2));
		m_total.m_proteinTotal += wxAtoi(this->GetItemText(i, 3));
		m_total.m_fiberTotal += wxAtoi(this->GetItemText(i, 4));
	}
	// set the total
	this->SetItem(0, 1, std::to_string(m_total.m_calTotal));
	this->SetItem(0, 2, std::to_string(m_total.m_carbTotal));
	this->SetItem(0, 3, std::to_string(m_total.m_proteinTotal));
	this->SetItem(0, 4, std::to_string(m_total.m_fiberTotal));
}

void CalorieList::Init()
{
	this->SetupMenu();
	this->SetupColumns();
	this->SetupImageList();
	this->SetupTotalItem();
}

void CalorieList::SetupMenu()
{
	m_pMenu = new wxMenu();

	m_pMenu->Append(wxID_DELETE, _T("Delete"));
}

void CalorieList::SetupColumns()
{
	this->AppendColumn(_T("Food/Items"));
	this->AppendColumn(_T("Calories"));
	this->AppendColumn(_T("Carbohydrates (g)"), wxLIST_FORMAT_LEFT, 115);
	this->AppendColumn(_T("Protein (g)"));
	this->AppendColumn(_T("Fibre (g)"));
}

void CalorieList::SetupImageList()
{
	m_pImageList = new wxImageList(16, 16);

	m_calorieBmp = wxBitmap(path_data::dataDir + _T("\\Images\\calorie_small.png"), wxBITMAP_TYPE_PNG);
	m_calorieBmp.ResetAlpha();

	m_pImageList->Add(m_calorieBmp);
	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void CalorieList::SetupTotalItem()
{
	this->InsertItem(0, _T("Total"));
	this->SetItem(0, 1, _T("0"));
	this->SetItem(0, 2, _T("0"));
	this->SetItem(0, 3, _T("0"));
	this->SetItem(0, 4, _T("0"));
}

// Events

void CalorieList::OnRightClick(wxListEvent& event)
{
	this->PopupMenu(m_pMenu);
}

void CalorieList::OnDoubleClick(wxListEvent& event)
{
}

void CalorieList::OnDeleteItem(wxCommandEvent& event)
{
	int selected = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

	// test if the selected item index is greater than 0 because we don't want to delete the total
	if (selected > 0 && wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
	{
		this->DeleteItem(selected);
		this->UpdateTotal();
	}
}
