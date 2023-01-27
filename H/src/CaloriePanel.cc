#include <wx/msgdlg.h>
#include <wx/textfile.h>
#include <wx/config.h>
#include <wx/file.h>
#include <wx/filedlg.h>
#include <wx/string.h>
#include "CaloriePanel.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"

// CalorieList event table
BEGIN_EVENT_TABLE(CalorieList, wxListView)
	EVT_LIST_ITEM_RIGHT_CLICK(wxID_ANY, CalorieList::OnRightClick)
	EVT_LIST_ITEM_ACTIVATED(wxID_ANY, CalorieList::OnDoubleClick)
	EVT_MENU(wxID_DELETE, CalorieList::OnDeleteItem)
END_EVENT_TABLE()

CaloriePanel::CaloriePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style, _T("caloriepanel"))
{
	this->Init();

	// Bind events
	m_pSearchButton->Bind(wxEVT_BUTTON, &CaloriePanel::OnSearch, this, static_cast<int>(CP::ID_SEARCH));
	m_pAddButton->Bind(wxEVT_BUTTON, &CaloriePanel::OnNewItem, this, static_cast<int>(CP::ID_NEW_ITEM));
	m_pSaveButton->Bind(wxEVT_BUTTON, &CaloriePanel::OnSaveInformation, this, wxID_SAVE);
}

CaloriePanel::~CaloriePanel()
{
	// Unbind events
	m_pSearchButton->Unbind(wxEVT_BUTTON, &CaloriePanel::OnSearch, this, static_cast<int>(CP::ID_SEARCH));
	m_pAddButton->Unbind(wxEVT_BUTTON, &CaloriePanel::OnNewItem, this, static_cast<int>(CP::ID_NEW_ITEM));
	m_pSaveButton->Unbind(wxEVT_BUTTON, &CaloriePanel::OnSaveInformation, this, wxID_SAVE);
}

void CaloriePanel::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void CaloriePanel::SetupControls()
{
	m_pCalorieList = new CalorieList(this, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);

	m_searchBmp = wxBitmap(path_data::dataDir + _T("\\Images\\search.png"), wxBITMAP_TYPE_PNG);
	m_addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_saveBmp = wxBitmap(path_data::dataDir + _T("\\Images\\save.png"), wxBITMAP_TYPE_PNG);

	m_pSearchButton = new wxBitmapButton(this, static_cast<int>(CP::ID_SEARCH), m_searchBmp, wxDefaultPosition, wxDefaultSize);
	m_pSearchButton->SetToolTip(_T("Search a nutritional item in the catalog."));

	m_pAddButton = new wxBitmapButton(this, static_cast<int>(CP::ID_NEW_ITEM), m_addBmp, wxDefaultPosition, wxDefaultSize);
	m_pAddButton->SetToolTip(_T("Add a new nutritional item."));

	m_pSaveButton = new wxBitmapButton(this, wxID_SAVE, m_saveBmp, wxDefaultPosition, wxDefaultSize);
	m_pSaveButton->SetToolTip(_T("Save current information."));
}

void CaloriePanel::SetupSizers()
{
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pBoxSizer);

	wxBoxSizer* m_pHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pHorizontalSizer->Add(m_pSearchButton, wxSizerFlags().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pAddButton, wxSizerFlags().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pSaveButton, wxSizerFlags().Border(wxALL, 5));

	m_pBoxSizer->Add(m_pCalorieList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pBoxSizer->Add(m_pHorizontalSizer, wxSizerFlags().Border(wxALL, 5));
}

void CaloriePanel::AddNewItem()
{
	m_pAddItemDlg = new AddItemDlg(this, wxID_ANY, _T("Add Nutritional Item"), wxDefaultPosition, wxDefaultSize);
	m_pAddItemDlg->Show(true);

	if (m_pAddItemDlg->ShowModal() == wxID_OK)
	{
		m_pCalorieList->AddItem(m_pAddItemDlg->GetItemName(), m_pAddItemDlg);
	}
}

// Events

void CaloriePanel::OnSearch(wxCommandEvent& event)
{
	m_pNutritionCatalog = new NutritionCatalog(this, wxID_ANY, _T("Nutrition Catalog"), wxDefaultPosition, wxDefaultSize);
	m_pNutritionCatalog->Show(true);
}

void CaloriePanel::OnNewItem(wxCommandEvent& event)
{
	this->AddNewItem();
}

void CaloriePanel::OnSaveInformation(wxCommandEvent& event)
{
	wxString fileName, filePath;
	wxFile textFile;
	Total total = m_pCalorieList->GetTotal();

	// Create a text file to write to by opening a file dialog
	wxFileDialog* pOpenDialog = new wxFileDialog(this, _T("Save Nutrition Log"), wxEmptyString, _T("Nutrition.txt"), _T("Text files (*.txt)|*.txt"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (pOpenDialog->ShowModal() == wxID_OK)
	{
		fileName = pOpenDialog->GetFilename();
		filePath = pOpenDialog->GetPath();
		textFile.Create(filePath);
	}
	else return;

	// After the file has been created, check to see if it exists
	if (!textFile.Exists(filePath))
	{
		wxLogError(_T("Failed to create text file: %s"), fileName);
		return;
	}
	
	// Write the nutritional contents to the text file
	if (textFile.Open(filePath, wxFile::write))
	{
		textFile.Write(wxString("Total calories: ") << total.m_calTotal << '\n');
		textFile.Write(wxString("Total carbohydrates: ") << total.m_carbTotal << '\n');
		textFile.Write(wxString("Total protein: ") << total.m_proteinTotal << '\n');
		textFile.Write(wxString("Total fibre: ") << total.m_fiberTotal << '\n');

		// Include other information about the generated text file
		if (wxConfigBase::Get()->Read("/Preferences/IncludeDT", 0L))
		{
			textFile.Write(wxString("This nutrition sheet was generated ") << __DATE__ << " at [" << __TIME__ << "]\n");
		}
	}

	textFile.Close();
	pOpenDialog->Destroy();
}

// ======================== CalorieList class ========================

CalorieList::CalorieList(CaloriePanel* pCaloriePanel, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style), m_pCaloriePanel{ pCaloriePanel }
{
	this->Init();

	this->Bind(wxEVT_KEY_DOWN, &CalorieList::OnKey, this);
}

CalorieList::~CalorieList()
{
	this->Unbind(wxEVT_KEY_DOWN, &CalorieList::OnKey, this);
}

void CalorieList::AddItem(const wxString& item, AddItemDlg* pAddItemDlg)
{
	/*
	* When the user adds a new item, we want to insert it at index 1.
	* Doing this because the 0 index is the total, and that should be 'pinned' at the top of the list.
	*/
	this->InsertItem(1, item);
	this->SetItem(1, 1, std::to_string(pAddItemDlg->GetCalorieContent()));
	this->SetItem(1, 2, std::to_string(pAddItemDlg->GetCarbContent()));
	this->SetItem(1, 3, std::to_string(pAddItemDlg->GetProteinContent()));
	this->SetItem(1, 4, std::to_string(pAddItemDlg->GetFiberContent()));

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
	// Set the total by converting ints back into strings
	this->SetItem(0, 1, std::to_string(m_total.m_calTotal));
	this->SetItem(0, 2, std::to_string(m_total.m_carbTotal));
	this->SetItem(0, 3, std::to_string(m_total.m_proteinTotal));
	this->SetItem(0, 4, std::to_string(m_total.m_fiberTotal));
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