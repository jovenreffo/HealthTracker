#include <wx/msgdlg.h>
#include <wx/textfile.h>
#include <wx/config.h>
#include <wx/file.h>
#include <wx/filedlg.h>
#include <wx/string.h>
#include <wx/datetime.h>

#include "CaloriePanel.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"
#include "Nutrient Total/Total.hpp"

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
	m_pCalorieList = new CalorieList(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);

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
		NutrientContent nc{ m_pAddItemDlg->GetCalorieContent(), m_pAddItemDlg->GetProteinContent(), m_pAddItemDlg->GetCarbContent(), m_pAddItemDlg->GetFiberContent() };
		m_pCalorieList->AddItem(m_pAddItemDlg->GetItemName(), nc);
	}
}

// Events

void CaloriePanel::OnSearch(wxCommandEvent& event)
{
	m_pNutritionCatalog = new NutritionCatalog(m_pCalorieList, this, wxID_ANY, _T("Nutrition Catalog"), wxDefaultPosition, wxDefaultSize);
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
	wxFileDialog* pSaveDialog = new wxFileDialog(this, _T("Save Nutrition Log"), wxEmptyString, _T("Nutrition.txt"), _T("Text files (*.txt)|*.txt"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (pSaveDialog->ShowModal() == wxID_OK)
	{
		fileName = pSaveDialog->GetFilename();
		filePath = pSaveDialog->GetPath();
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
			wxDateTime dt;
			dt.SetToCurrent();

			textFile.Write(wxString("This nutrition sheet was generated: ") << dt.FormatDate());
		}
	}

	textFile.Close();
	pSaveDialog->Destroy();
}