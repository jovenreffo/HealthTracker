#include <wx/log.h>
#include <wx/filedlg.h>
#include <wx/string.h>
#include <wx/config.h>
#include <wx/datetime.h>
#include "Journal.h"

BEGIN_EVENT_TABLE(Journal, wxPanel)
	EVT_BUTTON(ID_SAVE_ENTRY, Journal::OnSaveToEntries)
	EVT_BUTTON(ID_EXPORT, Journal::OnExport)
END_EVENT_TABLE()

Journal::Journal(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
	this->LoadConfig();
}

Journal::~Journal()
{
	m_auiMgr.UnInit();
}

wxString Journal::GetDate()
{
	wxDateTime dt;
	dt.SetToCurrent();
	return dt.FormatDate();
}

void Journal::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupAUI();
}

void Journal::LoadConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath("/Preferences");

	// Check if the spellcheck option is active from the preferences panel and enable it on the local text ctrl
	if (pConfig->Read("Spellcheck", 0L) == 1L)
		m_pTextCtrl->EnableProofCheck(wxTextProofOptions::Default());

	// Check if the user has selected a custom font
	if (pConfig->Read("CheckFont", 0L) == 1L)
	{
		m_pTextCtrl->SetFont(wxFont(
			pConfig->Read("FontSize", 10L),
			static_cast<wxFontFamily>(pConfig->Read("FontFamily", static_cast<long>(wxFONTFAMILY_DEFAULT))),
			static_cast<wxFontStyle>(pConfig->Read("FontStyle", static_cast<long>(wxFONTSTYLE_NORMAL))),
			wxFONTWEIGHT_NORMAL,
			pConfig->Read("FontUnderline", 0L),
			pConfig->Read("FaceName", "")
		));
	}
}

void Journal::SetupControls()
{
	// Panels
	m_pTextPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pEntryPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	// Date
	m_date = this->GetDate();

	// Text
	m_pDateText = new wxStaticText(m_pTextPanel, wxID_STATIC, wxString("Date: ") << m_date, wxDefaultPosition, wxDefaultSize);
	m_pMessageText = new wxStaticText(m_pTextPanel, wxID_STATIC, _T("What is going on today?"), wxDefaultPosition, wxDefaultSize);
	m_pPrevEntryText = new wxStaticText(m_pEntryPanel, wxID_STATIC, _T("Previous Entries:"), wxDefaultPosition, wxDefaultSize);

	// Control classes
	m_pTextCtrl = new wxTextCtrl(m_pTextPanel, ID_ENTRY_TEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2, wxDefaultValidator, _T("journalctrl"));
	m_pEntryList = new EntryList(m_pTextCtrl, m_pEntryPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pTextCtrl->DragAcceptFiles(true);

	// Buttons
	m_pSaveButton = new wxButton(m_pTextPanel, ID_SAVE_ENTRY, _T("Save to Entries"), wxDefaultPosition, wxDefaultSize);
	m_pExportButton = new wxButton(m_pTextPanel, ID_EXPORT, _T("Export"), wxDefaultPosition, wxDefaultSize);
}

void Journal::SetupSizers()
{
	// Start by arranging the elements for m_pTextPanel
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pTextPanel->SetSizerAndFit(m_pTopSizer);

	m_pButtonSizer->Add(m_pSaveButton, 0, wxALIGN_LEFT | wxALL, 5);
	m_pButtonSizer->Add(m_pExportButton, 0, wxALIGN_LEFT | wxALL, 5);

	m_pTopSizer->Add(m_pDateText, 0, wxLEFT | wxALL, 5);
	m_pTopSizer->Add(m_pMessageText, 0, wxLEFT | wxALL, 5);
	m_pTopSizer->Add(m_pTextCtrl, 1, wxEXPAND | wxALL, 5);
	m_pTopSizer->Add(m_pButtonSizer);

	// for m_pEntryPanel
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pEntryPanel->SetSizerAndFit(m_pTopSizer);
	m_pTopSizer->Add(m_pPrevEntryText, 0, wxLEFT | wxALL, 5);
	m_pTopSizer->Add(m_pEntryList, 1, wxEXPAND | wxALL, 5);

	// this
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);
	m_pTopSizer->Add(m_pTextPanel, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pEntryPanel, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

void Journal::SetupAUI()
{
	// Tell wxAUI to manage this top-level panel
	m_auiMgr.SetManagedWindow(this);

	// add the panels to the AUI controller
	m_auiMgr.AddPane(m_pTextPanel, wxAuiPaneInfo().Centre().Resizable(true).MinSize(wxSize(200, -1)).CloseButton(false).CaptionVisible(false));
	m_auiMgr.AddPane(m_pEntryPanel, wxAuiPaneInfo().Bottom().Resizable(true).MinSize(wxSize(200, 200)).CloseButton(false));

	// update the aui and commit changes
	m_auiMgr.Update();
}

// Events

void Journal::OnSaveToEntries(wxCommandEvent& event)
{
	m_pEntryDialog = new EntryDialog(this, wxID_ANY, _T("Add New Entry"));

	if (m_pEntryDialog->ShowModal() == wxID_OK)
	{
		// Save the item to the pair list
		m_pEntryList->AddItem(m_pEntryDialog->GetEntryName(), m_pTextCtrl->GetValue());
	}
}

void Journal::OnExport(wxCommandEvent& event)
{
	wxFileDialog* pFileDialog = new wxFileDialog(this, _T("Save entry"), wxEmptyString, wxEmptyString, _T("Text Files (*.txt)|*.txt"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (pFileDialog->ShowModal() == wxID_OK)
	{
		m_pTextCtrl->SaveFile(pFileDialog->GetPath());
		m_bFileSaved = true;
	}

	pFileDialog->Destroy();
}
