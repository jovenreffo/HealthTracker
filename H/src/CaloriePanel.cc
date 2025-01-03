#include <wx/msgdlg.h>
#include <wx/textfile.h>
#include <wx/config.h>
#include <wx/file.h>
#include <wx/filedlg.h>
#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/valgen.h>

#include "CaloriePanel.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"
#include "Nutrient Total/Total.hpp"

// ===== ToolsWindow =====

ToolsWindow::ToolsWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->InitToolsWindow();

	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &ToolsWindow::OnOK, this, wxID_OK);
	m_pHtmlWin->Bind(wxEVT_HTML_LINK_CLICKED, &ToolsWindow::OnLinkClicked, this);
}

ToolsWindow::~ToolsWindow()
{
	// Unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &ToolsWindow::OnOK, this, wxID_OK);
	m_pHtmlWin->Unbind(wxEVT_HTML_LINK_CLICKED, &ToolsWindow::OnLinkClicked, this);
}

void ToolsWindow::InitToolsWindow()
{
	this->SetupHTMLWindow();
	this->SetupButtons();
	this->SetupSizers();
	this->SetupSizing();
}

void ToolsWindow::SetupHTMLWindow()
{
	m_pHtmlWin = new wxHtmlWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_DEFAULT_STYLE);
	m_pHtmlWin->LoadPage(path_data::dataDir + _T("\\H\\src\\HTML\\nutrition_tools.html"));
	m_pHtmlWin->SetBorders(0);
	m_pHtmlWin->SetSize(wxSize(m_pHtmlWin->GetInternalRepresentation()->GetWidth(), m_pHtmlWin->GetInternalRepresentation()->GetHeight()));
}

void ToolsWindow::SetupButtons()
{
	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
}

void ToolsWindow::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopSizer->Add(m_pHtmlWin, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 10));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pOk, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
}

void ToolsWindow::SetupSizing()
{
	this->SetMinSize(TW_SIZE);
	this->SetInitialSize(TW_SIZE);
}

void ToolsWindow::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void ToolsWindow::OnLinkClicked(wxHtmlLinkEvent& event)
{
	// If it is a valid link containing the proper prefixed, launch the default browser.
	if (event.GetLinkInfo().GetHref().StartsWith("https://") || event.GetLinkInfo().GetHref().StartsWith("http://"))
		wxLaunchDefaultBrowser(event.GetLinkInfo().GetHref());
}

// ===== CPanelSettings =====

CPanelSettings::CPanelSettings(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();

	// Bind events
	m_pCalorieGoal->Bind(wxEVT_TEXT_ENTER, &CPanelSettings::OnEnter, this);
	m_pProteinGoal->Bind(wxEVT_TEXT_ENTER, &CPanelSettings::OnEnter, this);
	m_pOk->Bind(wxEVT_BUTTON, &CPanelSettings::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &CPanelSettings::OnCancel, this, wxID_CANCEL);
	m_pViewTools->Bind(wxEVT_BUTTON, &CPanelSettings::OnViewTools, this);
}

CPanelSettings::~CPanelSettings()
{
	// Unbind events
	m_pCalorieGoal->Unbind(wxEVT_TEXT_ENTER, &CPanelSettings::OnEnter, this);
	m_pProteinGoal->Unbind(wxEVT_TEXT_ENTER, &CPanelSettings::OnEnter, this);
	m_pOk->Unbind(wxEVT_BUTTON, &CPanelSettings::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &CPanelSettings::OnCancel, this, wxID_CANCEL);
	m_pViewTools->Unbind(wxEVT_BUTTON, &CPanelSettings::OnViewTools, this);
}

void CPanelSettings::SetCalorieCtrl(int val)
{
	m_pCalorieGoal->SetValue(val);
}

void CPanelSettings::SetProteinCtrl(int val)
{
	m_pProteinGoal->SetValue(val);
}

void CPanelSettings::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void CPanelSettings::SetupControls()
{
	m_pCalorieGoal = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000, 0);
	m_pCalorieGoal->SetValidator(wxGenericValidator(&m_calorieGoal));

	m_pProteinGoal = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000, 0);
	m_pProteinGoal->SetValidator(wxGenericValidator(&m_proteinGoal));

	m_pViewTools = new wxButton(this, (int)(CPS::ID_VIEW_TOOLS), _T("View Tools"));
	m_pViewTools->SetBitmap(wxBitmap(path_data::dataDir + _T("\\Images\\wrench.png"), wxBITMAP_TYPE_PNG));

	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"));
}

void CPanelSettings::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pControlSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	this->SetSizerAndFit(m_pTopSizer);

	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Calorie Goal:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pCalorieGoal, wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Protein Goal:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pProteinGoal, wxSizerFlags().Border(wxALL, 5));

	m_pTopSizer->Add(m_pControlSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
	m_pTopSizer->Add(m_pViewTools, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
}

void CPanelSettings::SetupSizing()
{
	wxSize sz{ this->GetBestSize() };
	this->SetMinSize(sz);
	this->SetInitialSize(wxSize(sz.GetWidth() + 50, sz.GetHeight() + 35));
}

void CPanelSettings::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void CPanelSettings::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

void CPanelSettings::OnEnter(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void CPanelSettings::OnViewTools(wxCommandEvent& event)
{
	m_pToolsWindow = new ToolsWindow(this, wxID_ANY);
	m_pToolsWindow->Show(true);

	if (m_pToolsWindow->ShowModal() == wxID_OK)
	{
	}
}

// ===== CaloriePanel =====

CaloriePanel::CaloriePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style, _T("caloriepanel"))
{
	this->Init();
	this->LoadConfig();

	// Bind events
	m_pSearchButton->Bind(wxEVT_BUTTON, &CaloriePanel::OnSearch, this, (int)(CP::ID_SEARCH));
	m_pAddButton->Bind(wxEVT_BUTTON, &CaloriePanel::OnNewItem, this, (int)(CP::ID_NEW_ITEM));
	m_pSaveButton->Bind(wxEVT_BUTTON, &CaloriePanel::OnSaveInformation, this, wxID_SAVE);
	m_pSettingsButton->Bind(wxEVT_BUTTON, &CaloriePanel::OnOpenSettings, this, (int)(CP::ID_SETTINGS));
}

CaloriePanel::~CaloriePanel()
{
	// Save config
	this->SaveConfig();

	// Unbind events
	m_pSearchButton->Unbind(wxEVT_BUTTON, &CaloriePanel::OnSearch, this, static_cast<int>(CP::ID_SEARCH));
	m_pAddButton->Unbind(wxEVT_BUTTON, &CaloriePanel::OnNewItem, this, static_cast<int>(CP::ID_NEW_ITEM));
	m_pSaveButton->Unbind(wxEVT_BUTTON, &CaloriePanel::OnSaveInformation, this, wxID_SAVE);
	m_pSettingsButton->Unbind(wxEVT_BUTTON, &CaloriePanel::OnOpenSettings, this, (int)(CP::ID_SETTINGS));
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
	m_settingsBmp = wxBitmap(path_data::dataDir + _T("\\Images\\settings_30.png"), wxBITMAP_TYPE_PNG);

	m_pSearchButton = new wxBitmapButton(this, (int)(CP::ID_SEARCH), m_searchBmp, wxDefaultPosition, wxDefaultSize);
	m_pSearchButton->SetToolTip(_T("Search a nutritional item in the catalog."));

	m_pAddButton = new wxBitmapButton(this, (int)(CP::ID_NEW_ITEM), m_addBmp, wxDefaultPosition, wxDefaultSize);
	m_pAddButton->SetToolTip(_T("Add a new nutritional item."));

	m_pSaveButton = new wxBitmapButton(this, wxID_SAVE, m_saveBmp, wxDefaultPosition, wxDefaultSize);
	m_pSaveButton->SetToolTip(_T("Save current information."));

	m_pSettingsButton = new wxBitmapButton(this, (int)(CP::ID_SETTINGS), m_settingsBmp, wxDefaultPosition, wxDefaultSize);
	m_pSettingsButton->SetToolTip(_T("Open settings."));
}

void CaloriePanel::SetupSizers()
{
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pBoxSizer);

	wxBoxSizer* m_pHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pHorizontalSizer->Add(m_pSearchButton, wxSizerFlags().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pAddButton, wxSizerFlags().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pSaveButton, wxSizerFlags().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pSettingsButton, wxSizerFlags().Border(wxALL, 5));

	m_pBoxSizer->Add(m_pCalorieList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pBoxSizer->Add(m_pHorizontalSizer, wxSizerFlags().Border(wxALL, 5));
}

void CaloriePanel::SaveConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	// create a new directory in which to store the nutrient & macro goals
	pConfig->SetPath(_T("/CaloriePanel/Goals"));

	// write the variables to the config
	pConfig->Write(_T("CalorieGoal"), m_calorieGoal);
	pConfig->Write(_T("ProteinGoal"), m_proteinGoal);
}

void CaloriePanel::LoadConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/CaloriePanel/Goals"));

	m_calorieGoal = pConfig->Read(_T("CalorieGoal"), 0L);
	m_proteinGoal = pConfig->Read(_T("ProteinGoal"), 0L);

#ifdef _DEBUG
	//wxLogMessage(_T("Calorie goal: %d\nProtein goal: %d"), m_calorieGoal, m_proteinGoal);
#endif

	// Get the calorie & protein totals from the list
	int calorieTotal{ m_pCalorieList->GetTotal().GetCalTotal() };
	int proteinTotal{ m_pCalorieList->GetTotal().GetProteinTotal() };
	NutrientGoals ng{ m_calorieGoal, m_proteinGoal };
	m_pCalorieList->SetNutrientGoals(ng);

	// test if the values are valid, then assign them to the list
	if (m_calorieGoal)
		m_pCalorieList->SetItem(0, 1, wxString(std::to_string(calorieTotal)) << '/' << std::to_string(m_calorieGoal));

	if (m_proteinGoal)
		m_pCalorieList->SetItem(0, 3, wxString(std::to_string(proteinTotal)) << '/' << std::to_string(m_proteinGoal));
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

void CaloriePanel::OnOpenSettings(wxCommandEvent& event)
{
	m_pPanelSettings = new CPanelSettings(this, wxID_ANY);
	m_pPanelSettings->Show(true);

	// check to see if the valuesa are active for loading onto the dialog
	if (m_calorieGoal || m_proteinGoal)
	{
		m_pPanelSettings->SetCalorieCtrl(m_calorieGoal);
		m_pPanelSettings->SetProteinCtrl(m_proteinGoal);
	}

	if (m_pPanelSettings->ShowModal() == wxID_OK)
	{
		// retrieve data
		NutrientGoals ng{ m_pPanelSettings->GetCalorieGoal() , m_pPanelSettings->GetProteinGoal() };
		int calorieTotal{ m_pCalorieList->GetTotal().GetCalTotal() };
		int proteinTotal{ m_pCalorieList->GetTotal().GetProteinTotal() };
		m_pCalorieList->SetNutrientGoals(ng);

		if (ng.GetCalorieGoal() > 0)
			m_pCalorieList->SetItem(0, 1, wxString(std::to_string(calorieTotal)) << '/' << std::to_string(ng.GetCalorieGoal()));

		if (ng.GetProteinGoal() > 0)
			m_pCalorieList->SetItem(0, 3, wxString(std::to_string(proteinTotal)) << '/' << std::to_string(ng.GetProteinGoal()));

		// assign values to member variables again
		m_calorieGoal = m_pPanelSettings->GetCalorieGoal();
		m_proteinGoal = m_pPanelSettings->GetProteinGoal();
	}
}
