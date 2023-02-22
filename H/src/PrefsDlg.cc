#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/config.h>
#include <wx/translation.h>
#include <wx/app.h>
#include <wx/fontdlg.h>
#include <wx/valgen.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include "PrefsDlg.h"
#include "Font/Font.hpp"
#include "Journal.h"
#include "WorkoutWindow.h"
#include "Window.h"

namespace lang
{
	wxString GetUILanguage()
	{
		wxString lang = wxConfig::Get()->Read("ui_language");
		if (lang != wxEmptyString && lang != "default")
			return lang;
		else
			return wxEmptyString;
	}
}

enum class Prefs
{
	ID_CHECK_FONT,
	ID_SELECT_FONT,
	ID_RESET_FONT,
	ID_SPELL_CHECK,
	ID_INCLUDE_DT // include date and time in the generation of nutrition sheet
};

class GeneralPagePanel: public wxPanel
{
private:
	wxCheckBox* m_pCheckCustomFont;
	wxCheckBox* m_pEnableSpellCheck;
	wxButton* m_pSelectFont;
	wxButton* m_pResetDefFont;
	wxFontDialog* m_pFontDialog;
	wxTextCtrl* m_pJournalTxtCtrl;
	wxStaticText* m_pWhatFont;

	wxFont m_selectedFont;
	wxFont m_defaultFont;
	wxString m_faceName;

public:
	GeneralPagePanel(wxWindow* parent)
		: wxPanel(parent, -1, wxDefaultPosition, wxDefaultSize, 0L, _("generalpagepanel"))
	{
		this->SetupWindowPointers();
		wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
		this->SetSizerAndFit(pTopSizer);

		// =============== environment ===============
		// Initialization
		wxStaticText* pEnvText = new wxStaticText(this, wxID_STATIC, _("Environment"));
		pEnvText->SetFont(Fonts::GetBoldFont(10));
		pTopSizer->Add(pEnvText, wxSizerFlags().CentreHorizontal().Left().Border(wxALL, 5));

		wxFlexGridSizer* pEnvSizer = new wxFlexGridSizer(2, wxSize(5, 1));
		pEnvSizer->AddGrowableCol(1);
		pTopSizer->Add(pEnvSizer, wxSizerFlags().Expand());

		m_pFontDialog = new wxFontDialog(this);
		m_pCheckCustomFont = new wxCheckBox(this, static_cast<int>(Prefs::ID_CHECK_FONT), _("Use custom font in text fields:"));
		m_pEnableSpellCheck = new wxCheckBox(this, static_cast<int>(Prefs::ID_SPELL_CHECK), _("Check spelling"));
		m_pSelectFont = new wxButton(this, static_cast<int>(Prefs::ID_SELECT_FONT), _("Select..."), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
		m_pResetDefFont = new wxButton(this, static_cast<int>(Prefs::ID_RESET_FONT), _("Reset"), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
		m_pWhatFont = new wxStaticText(this, wxID_STATIC, wxString(_("Current font: ")) << m_pCheckCustomFont->GetFont().GetFaceName(), wxDefaultPosition, wxDefaultSize);
		// control configurations
		m_pSelectFont->Disable();
		m_pWhatFont->SetForegroundColour(wxColour(128, 128, 128));
		m_defaultFont = m_pCheckCustomFont->GetFont();

		// Add items to the sizer
		pEnvSizer->Add(m_pEnableSpellCheck, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pEnvSizer->AddSpacer(5);
		pEnvSizer->Add(m_pCheckCustomFont, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pEnvSizer->Add(m_pSelectFont, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pEnvSizer->Add(m_pWhatFont, wxSizerFlags().CentreVertical().Expand().Border(wxLEFT, 5));
		pEnvSizer->AddSpacer(5);
		pEnvSizer->Add(new wxStaticText(this, wxID_STATIC, _("Use default font:")), wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pEnvSizer->Add(m_pResetDefFont, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));

		// Event binding
		m_pCheckCustomFont->Bind(wxEVT_CHECKBOX, &GeneralPagePanel::OnUseCustomFont, this);
		m_pSelectFont->Bind(wxEVT_BUTTON, [=](wxCommandEvent&){ this->DoFontSelect(); }, -1);
		m_pSelectFont->Bind(wxEVT_UPDATE_UI, &GeneralPagePanel::UpdateFontSelect, this);
		m_pResetDefFont->Bind(wxEVT_BUTTON, &GeneralPagePanel::OnResetFont, this);
		m_pEnableSpellCheck->Bind(wxEVT_CHECKBOX, &GeneralPagePanel::OnSpellCheck, this);
		
		this->LoadConfig();
		this->Fit();
		this->SetMinSize(wxSize(300, 350));
	}

	~GeneralPagePanel()
	{
		this->SaveToConfig();
	}

	void LoadConfig()
	{
		wxConfigBase* pConfig = wxConfigBase::Get();
		if (pConfig == nullptr)
			return;

		pConfig->SetPath(_("/Preferences"));

		m_pCheckCustomFont->SetValue(pConfig->Read("CheckFont", 0L));
		m_faceName = pConfig->Read("FaceName", "");
		m_pWhatFont->SetLabel(wxString(_("Current font: ")) << m_faceName);

		m_pEnableSpellCheck->SetValue(pConfig->Read("Spellcheck", 0L));

		// Load the font
		if (m_pCheckCustomFont->IsChecked())
		{
			m_selectedFont.SetPointSize(pConfig->Read("FontSize", 10L));
			m_selectedFont.SetFamily(static_cast<wxFontFamily>(pConfig->Read("FontFamily", static_cast<long>(wxFONTFAMILY_DEFAULT))));
			m_selectedFont.SetStyle(static_cast<wxFontStyle>(pConfig->Read("FontStyle", static_cast<long>(wxFONTSTYLE_NORMAL))));
			m_selectedFont.SetNumericWeight(pConfig->Read("FontWeight", static_cast<long>(wxFONTWEIGHT_NORMAL)));
			m_selectedFont.SetUnderlined(pConfig->Read("FontUnderline", 0L));
			m_selectedFont.SetFaceName(m_faceName);
			m_pJournalTxtCtrl->SetFont(m_selectedFont);
		}
	}

	void SaveToConfig()
	{
		wxConfigBase* pConfig = wxConfigBase::Get();
		if (pConfig == nullptr)
			return;

		pConfig->Write("/Preferences/CheckFont", m_pCheckCustomFont->GetValue());
		pConfig->Write("/Preferences/FaceName", m_faceName);
		pConfig->Write("/Preferences/Spellcheck", m_pEnableSpellCheck->GetValue());
		
		// save font information
		if (m_selectedFont.IsOk())
		{
			pConfig->Write("/Preferences/FontSize", static_cast<long>(m_selectedFont.GetPointSize()));
			pConfig->Write("/Preferences/FontFamily", static_cast<long>(m_selectedFont.GetFamily()));
			pConfig->Write("/Preferences/FontStyle", static_cast<long>(m_selectedFont.GetStyle()));
			pConfig->Write("/Preferences/FontWeight", static_cast<long>(m_selectedFont.GetNumericWeight()));
			pConfig->Write("/Preferences/FontUnderline", m_selectedFont.GetUnderlined());
		}
	}

	virtual bool TransferDataToWindow() override
	{
		return true;
	}

private:

	void SetupWindowPointers()
	{
		// trace back to main frame to find the entry list's text control, as it is a distant child window
		wxWindow* pMainWin = this->GetParent()->GetParent()->GetParent()->FindWindow(_T("journalctrl"));
		if (pMainWin)
		{
			m_pJournalTxtCtrl = dynamic_cast<wxTextCtrl*>(pMainWin); // cast the window to a wxTextCtrl so we have control over it
		}
	}

	// events

	void OnResetFont(wxCommandEvent& event)
	{
		m_selectedFont = m_defaultFont;
		m_faceName = m_defaultFont.GetFaceName();
		this->SaveToConfig();
		m_pJournalTxtCtrl->SetFont(m_defaultFont);
		m_pWhatFont->SetLabel(wxString(_("Current font: Segoe UI")));

		m_pCheckCustomFont->SetValue(0);
		m_pSelectFont->Enable(false);
	}

	void UpdateFontSelect(wxUpdateUIEvent& event)
	{
		if (m_pCheckCustomFont->IsChecked())
			event.Enable(true);
	}

	void DoFontSelect()
	{
		m_pFontDialog = new wxFontDialog(this);
		m_pFontDialog->Show(true);
		if (m_pFontDialog->ShowModal() == wxID_OK)
		{
			wxFontData fontData = m_pFontDialog->GetFontData();
			m_selectedFont = fontData.GetChosenFont();

			// set the font of the entry list
			if (m_selectedFont.IsOk())
			{
				m_pJournalTxtCtrl->SetFont(m_selectedFont);
				m_faceName = m_selectedFont.GetFaceName();
				m_pWhatFont->SetLabel(wxString(_("Current font: ")) << m_faceName);
			}
		}
	}

	void OnUseCustomFont(wxCommandEvent& event)
	{
		if (event.IsChecked())
		{
			m_pSelectFont->Enable(true);
			if (m_selectedFont.IsOk())
			{
				m_pJournalTxtCtrl->SetFont(m_selectedFont);
			}
		}
		else
		{
			m_pSelectFont->Enable(false);
			// revert the font back to the original
			m_pJournalTxtCtrl->SetFont(m_defaultFont);
		}
	}

	void OnSpellCheck(wxCommandEvent& event)
	{
		if (event.IsChecked())
		{
			// Enable spell checking on the journal (wxWidgets 3.1.6 required)
			if (m_pJournalTxtCtrl != nullptr)
			{
				m_pJournalTxtCtrl->EnableProofCheck(wxTextProofOptions::Default());
			}
		}
		else
		{
			// Disable spell checking
			if (m_pJournalTxtCtrl != nullptr)
			{
				m_pJournalTxtCtrl->EnableProofCheck(wxTextProofOptions::Disable());
			}
		}
	}
};

class GeneralPage: public wxStockPreferencesPage
{
public:
	GeneralPage(): wxStockPreferencesPage(wxStockPreferencesPage::Kind::Kind_General)
	{
	}

	virtual wxWindow* CreateWindow(wxWindow* parent) override
	{
		return new GeneralPagePanel(parent);
	}
};

class AdvancedPagePanel: public wxPanel
{
private:
	wxCheckBox* m_pIncludeDT;
	bool m_bIncludeDT;

	// for the ExercisePanel's save event in DynamicPlan
	wxCheckBox* m_pIncludeDTReps;
	bool m_bIncludeDTReps;

public:
	AdvancedPagePanel(wxWindow* parent)
		: wxPanel(parent)
	{
		wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
		this->SetSizerAndFit(pTopSizer);

		wxStaticText* pDesc = new wxStaticText(this, wxID_STATIC, _("These options directly affect the program's configuration."));
		pDesc->SetForegroundColour(wxColour(128, 128, 128));

		wxStaticText* pResetConfigTxt = new wxStaticText(this, wxID_STATIC, _("Reset program configuration:"));
		wxButton* pResetConfigBtn = new wxButton(this, wxID_ANY, _("Reset"));

		m_pIncludeDT = new wxCheckBox(this, static_cast<int>(Prefs::ID_INCLUDE_DT), _T("Include date and time in nutrition sheet"), wxDefaultPosition, wxDefaultSize, 0L, wxGenericValidator(&m_bIncludeDT));
		m_pIncludeDTReps = new wxCheckBox(this, wxID_ANY, _T("Include date and time in exercise sheet"), wxDefaultPosition, wxDefaultSize, 0L, wxGenericValidator(&m_bIncludeDTReps));

		// Event binding
		pResetConfigBtn->Bind(wxEVT_BUTTON, &AdvancedPagePanel::OnResetConfig, this);

		wxFlexGridSizer* pAdvancedSizer = new wxFlexGridSizer(2, wxSize(5, 1));

		pTopSizer->Add(pDesc, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
		pTopSizer->Add(pAdvancedSizer, wxSizerFlags().Expand());
		pAdvancedSizer->Add(pResetConfigTxt, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
		pAdvancedSizer->Add(pResetConfigBtn, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
		pTopSizer->Add(m_pIncludeDT, wxSizerFlags().Left().Border(wxALL, 5));
		pTopSizer->Add(m_pIncludeDTReps, wxSizerFlags().Left().Border(wxALL, 5));

		this->LoadConfig();
		this->Fit();
	}

	~AdvancedPagePanel()
	{
		this->SaveToConfig();
	}

private:
	void OnResetConfig(wxCommandEvent& event)
	{
		wxConfigBase* pConfig = wxConfigBase::Get();

		if (pConfig == nullptr)
		{
			wxLogError(_("No configuration to delete."));
			return;
		}

		if (pConfig->DeleteAll())
		{
			wxLogMessage(_("Successfully deleted program configuration."));
			delete wxConfigBase::Set(nullptr);
			wxConfigBase::DontCreateOnDemand();
		}
		else
		{
			wxLogError(_("Failed to delete program configuration."));
		}
	}

	void LoadConfig()
	{
		wxConfigBase* pConfig = wxConfigBase::Get();
		if (pConfig == nullptr)
			return;

		pConfig->SetPath(_("/Preferences"));

		m_pIncludeDT->SetValue(pConfig->Read("IncludeDT", 0L));
		m_pIncludeDTReps->SetValue(pConfig->Read("IncludeDTReps", 0L));
	}

	void SaveToConfig()
	{
		wxConfigBase* pConfig = wxConfigBase::Get();
		if (pConfig == nullptr)
			return;

		pConfig->SetPath(_("/Preferences"));

		pConfig->Write("IncludeDT", m_pIncludeDT->GetValue());
		pConfig->Write("IncludeDTReps", m_pIncludeDTReps->GetValue());
	}

	virtual bool TransferDataToWindow() override
	{
		return true;
	}
};

class AdvancedPage: public wxStockPreferencesPage
{
public:
	AdvancedPage() : wxStockPreferencesPage(wxStockPreferencesPage::Kind::Kind_Advanced)
	{
	}

	virtual wxWindow* CreateWindow(wxWindow* parent) override
	{
		return new AdvancedPagePanel(parent);
	}
};

PrefsDlg::PrefsDlg(const wxString& title)
	: wxPreferencesEditor(title)
{
	this->AddPage(new GeneralPage());
	this->AddPage(new AdvancedPage());
}