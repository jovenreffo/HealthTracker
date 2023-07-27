#include <wx/log.h>
#include <wx/filedlg.h>
#include <wx/string.h>
#include <wx/config.h>
#include <wx/datetime.h>
#include <wx/msgdlg.h>
#include <wx/stringops.h>
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
	this->LoadEntriesFromConfig();
}

Journal::~Journal()
{
	this->UpdateConfigPerspective();
	this->SaveEntriesToConfig();
	m_auiMgr.UnInit();
}

wxString Journal::GetDate()
{
	wxDateTime dt;
	dt.SetToCurrent();
	return dt.FormatDate();
}

void Journal::ResetPerspective()
{
	if (m_defPerspective == wxEmptyString)
		return;

	// Update the AUI
	m_auiMgr.LoadPerspective(m_defPerspective, true);
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

	pConfig->SetPath(_T("/Preferences/"));

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

	// Load the window perspective
	pConfig->SetPath(_T("/Journal/"));
	m_defPerspective = _T("layout2|name=TextPane;caption=;state=1020;dir=5;layer=0;row=0;pos=0;prop=100000;bestw=200;besth=0;minw=200;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=EntryPane;caption=;state=2044;dir=3;layer=0;row=0;pos=0;prop=100000;bestw=200;besth=200;minw=200;minh=200;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|dock_size(5,0,0)=202|dock_size(3,0,0)=219|");
	m_auiMgr.LoadPerspective(pConfig->Read(_T("Perspective"), m_defPerspective), true);
}

void Journal::UpdateConfigPerspective()
{
	// Update the program config using SavePerspective
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/Journal/"));

	m_perspective = m_auiMgr.SavePerspective();
	pConfig->Write(_T("Perspective"), m_perspective);
}

void Journal::SaveEntriesToConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	// Set the config path to something different in order to keep things separate
	pConfig->SetPath(_T("/Journal/EntryNames"));

	// Save an integer for the number of entries
	m_numEntries = m_pEntryList->GetItemCount();
	pConfig->Write(_T("NumEntries"), m_numEntries);

	// Loop through all the entries and save their strings to the program configuration
	// First: for the entry names
	for (auto i{ 0 }; i < m_pEntryList->GetItemCount(); ++i, ++m_nameID)
	{
		// Convert the m_nameID to a string and associate it with the current item's text
		pConfig->Write(std::to_string(i), m_pEntryList->GetItemText(i));
	}

	// Second: for the entry content
	pConfig->SetPath(_T("/Journal/EntryContent"));
	for (auto i{ 0 }; i < m_pEntryList->GetItemCount(); ++i)
	{
		// Recieve the content associated with index 'i'
		pConfig->Write(std::to_string(i), m_pEntryList->GetEntryContent()[i].GetContent());
	}
}

void Journal::LoadEntriesFromConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/Journal/EntryNames/"));
	m_numEntries = pConfig->Read(_T("NumEntries"), 0L);
	
	// setup an array for content
	wxArrayString entryContentArr;
	pConfig->SetPath(_T("/Journal/EntryContent"));
	for (auto i{ m_numEntries - 1 }; i >= 0; --i)
	{
		wxString curr;

		if (pConfig->Read(std::to_string(i), &curr))
			entryContentArr.Add(curr);
	}

	// load the entry names
	pConfig->SetPath(_T("/Journal/EntryNames/"));

	for (auto i{ m_numEntries - 1 }; i >= 0; --i)
	{
		wxString curr;

		if (pConfig->Read(std::to_string(i), &curr))
			m_pEntryList->AddItem(curr, entryContentArr[i]);
	}

#ifdef _DEBUG
	//wxLogMessage("%d", m_numEntries);
#endif
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
	m_pEntryList = new EntryList(&m_numEntries, m_pTextCtrl, m_pEntryPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
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
	m_auiMgr.AddPane(m_pTextPanel, wxAuiPaneInfo().Centre().Resizable(true).MinSize(wxSize(200, -1)).CloseButton(false).CaptionVisible(false).Name(_T("TextPane")));
	m_auiMgr.AddPane(m_pEntryPanel, wxAuiPaneInfo().Bottom().Resizable(true).MinSize(wxSize(200, 200)).CloseButton(false).Name(_T("EntryPane")));

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
