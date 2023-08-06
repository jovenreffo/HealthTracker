#include "CalorieList.h"
#include "StandardPath.hpp"

CalorieList::CalorieList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();

	// Bind Events
	this->Bind(wxEVT_KEY_DOWN, &CalorieList::OnKey, this);
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &CalorieList::OnRightClick, this);
	this->Bind(wxEVT_LIST_ITEM_ACTIVATED, &CalorieList::OnDoubleClick, this);
	m_pMenu->Bind(wxEVT_MENU, &CalorieList::OnDeleteItem, this, wxID_DELETE);
}

CalorieList::~CalorieList()
{
	this->Unbind(wxEVT_KEY_DOWN, &CalorieList::OnKey, this);
	this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &CalorieList::OnRightClick, this);
	this->Unbind(wxEVT_LIST_ITEM_ACTIVATED, &CalorieList::OnDoubleClick, this);
	m_pMenu->Unbind(wxEVT_MENU, &CalorieList::OnDeleteItem, this, wxID_DELETE);
}

//void CalorieList::AddItem(const wxString& item, AddItemDlg* pAddItemDlg)
//{
//	/*
//	* When the user adds a new item, we want to insert it at index 1.
//	* Doing this because the 0 index is the total, and that should be 'pinned' at the top of the list.
//	*/
//	this->InsertItem(1, item);
//	this->SetItem(1, 1, std::to_string( pAddItemDlg->GetCalorieContent() ));
//	this->SetItem(1, 2, std::to_string( pAddItemDlg->GetCarbContent() ));
//	this->SetItem(1, 3, std::to_string( pAddItemDlg->GetProteinContent() ));
//	this->SetItem(1, 4, std::to_string( pAddItemDlg->GetFiberContent() ));
//
//	this->UpdateTotal();
//}

void CalorieList::AddItem(const wxString& item, const NutrientContent& c)
{
	this->InsertItem(1, item);
	this->SetItem(1, 1, std::to_string( c.GetCalories() ));
	this->SetItem(1, 2, std::to_string( c.GetCarbohydrates() ));
	this->SetItem(1, 3, std::to_string( c.GetProtein() ));
	this->SetItem(1, 4, std::to_string( c.GetFiber() ));

	this->UpdateTotal();
}

void CalorieList::UpdateTotal()
{
	// To get an accurate calculation, clear what is currently begin held in the total
	m_total.ResetTotal();
	// Start the calculation at index 1, because the total should not be included
	for (auto i{ 1 }; i < this->GetItemCount(); ++i)
	{
		// At the current list index, get the string value of whatever is in the column (1, 2, 3, 4) and convert it to an int.
		m_total.m_calTotal += wxAtoi(this->GetItemText(i, 1));
		m_total.m_carbTotal += wxAtoi(this->GetItemText(i, 2));
		m_total.m_proteinTotal += wxAtoi(this->GetItemText(i, 3));
		m_total.m_fiberTotal += wxAtoi(this->GetItemText(i, 4));
	}

	if (m_nutrientGoals.IsActive())
	{
		// Check if the calorie goal is greater than 0, and only set it if it is.
		if (m_nutrientGoals.GetCalorieGoal() > 0)
			this->SetItem(0, 1, wxString(std::to_string(m_total.m_calTotal)) << '/' << m_nutrientGoals.GetCalorieGoal());

		// same for protein goal
		if (m_nutrientGoals.GetProteinGoal() > 0)
			this->SetItem(0, 3, wxString(std::to_string(m_total.m_proteinTotal)) << '/' << m_nutrientGoals.GetProteinGoal());

		// other nutrients
		this->SetItem(0, 2, std::to_string(m_total.m_carbTotal));
		this->SetItem(0, 4, std::to_string(m_total.m_fiberTotal));
		return;
	}
	else
	{
		// Set totals regularly
		this->SetItem(0, 1, std::to_string(m_total.m_carbTotal));
		this->SetItem(0, 2, std::to_string(m_total.m_carbTotal));
		this->SetItem(0, 3, std::to_string(m_total.m_proteinTotal));
		this->SetItem(0, 4, std::to_string(m_total.m_fiberTotal));
	}
}

void CalorieList::HandleDeleteItem()
{
	int selected = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

	// Test if the selected item index is greater than 0 because we don't want to delete the total
	if (selected > 0 && wxMessageBox(_T("Are you sure you want to delete this item?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
	{
		this->DeleteItem(selected);
		this->UpdateTotal();
	}
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
	this->AppendColumn(_T("Carbohydrates (g)"), wxLIST_FORMAT_LEFT, 115); // longer label, set custom column width
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
	// Insert the total at index 0, and any items after it come at index 1
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
	this->HandleDeleteItem();
}

void CalorieList::OnKey(wxKeyEvent& event)
{
	switch (event.GetUnicodeKey())
	{
	case WXK_DELETE:
		this->HandleDeleteItem();
		break;

	default:
		break;
	}

	event.Skip();
}