#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/config.h>
#include <wx/translation.h>
#include <wx/app.h>
#include <wx/fontdlg.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include "PrefsDlg.h"
#include "Font/Font.hpp"
#include "Journal.h"

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
};

class GeneralPagePanel: public wxPanel
{
private:
	wxCheckBox* m_pCheckCustomFont;
	wxButton* m_pSelectFont;
	wxFontDialog* m_pFontDialog;
	wxTextCtrl* m_pJournalTxtCtrl;
	wxStaticText* m_pWhatFont;

	wxFont m_selectedFont;
	wxString m_faceName;

public:
	GeneralPagePanel(wxWindow* parent)
		: wxPanel(parent)
	{
		

#ifdef _DEBUG
		// Test to make sure that the config is actually getting the values
		//wxLogMessage(_("%d"), pConfig->ReadLong("/Frame/x", 100));
#endif	

		this->SetupWindowPointers();
		wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
		this->SetSizerAndFit(pTopSizer);

		// =============== environment ===============
		wxStaticText* pEnvText = new wxStaticText(this, wxID_STATIC, _T("Environment"));
		pEnvText->SetFont(Fonts::GetBoldFont(10));
		pTopSizer->Add(pEnvText, wxSizerFlags().CentreHorizontal().Left().Border(wxALL, 5));


		// =============== appearance ===============
		wxStaticText* pAppearanceText = new wxStaticText(this, wxID_STATIC, _("Appearance"));
		pAppearanceText->SetFont(Fonts::GetBoldFont(10));
		pTopSizer->Add(pAppearanceText, wxSizerFlags().CentreHorizontal().Left().Border(wxALL, 5));

		wxFlexGridSizer* pAppearanceSizer = new wxFlexGridSizer(2, wxSize(5, 1));
		pAppearanceSizer->AddGrowableCol(1);
		pTopSizer->Add(pAppearanceSizer, wxSizerFlags().Expand());

		m_pFontDialog = new wxFontDialog(this);
		m_pCheckCustomFont = new wxCheckBox(this, (int)Prefs::ID_CHECK_FONT, _("Use custom font in text fields:"));
		m_pSelectFont = new wxButton(this, (int)Prefs::ID_SELECT_FONT, _("Select..."), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
		m_pSelectFont->Disable();
		m_pWhatFont = new wxStaticText(this, wxID_STATIC, wxString(_("Current font: ")) << m_pCheckCustomFont->GetFont().GetFaceName(), wxDefaultPosition, wxDefaultSize);
		m_pWhatFont->SetForegroundColour(wxColour(128, 128, 128));

		pAppearanceSizer->Add(m_pCheckCustomFont, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pAppearanceSizer->Add(m_pSelectFont, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pAppearanceSizer->Add(m_pWhatFont, wxSizerFlags().CentreVertical().Expand().Border(wxLEFT, 5));

		// Event binding
		m_pCheckCustomFont->Bind(wxEVT_CHECKBOX, &GeneralPagePanel::OnUseCustomFont, this);
		m_pSelectFont->Bind(wxEVT_BUTTON, [=](wxCommandEvent&){ this->DoFontSelect(); }, -1);
		m_pSelectFont->Bind(wxEVT_UPDATE_UI, &GeneralPagePanel::UpdateFontSelect, this);
		
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
		pConfig->SetPath(_("/Preferences"));

		m_pCheckCustomFont->SetValue(pConfig->Read("CheckFont", 1L) != 0);
		m_faceName = pConfig->Read("FaceName", "");
		m_pWhatFont->SetLabel(wxString(_("Current font: ")) << m_faceName);
	}

	void SaveToConfig()
	{
		wxConfigBase* pConfig = wxConfigBase::Get();
		if (pConfig == nullptr)
		{
			wxLogMessage(_T("Null config."));
			return;
		}

		pConfig->Write("/Preferences/CheckFont", m_pCheckCustomFont->GetValue());
		pConfig->Write("/Preferences/FaceName", m_faceName);
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
		m_pJournalTxtCtrl = dynamic_cast<wxTextCtrl*>(pMainWin); // cast the window to a wxTextCtrl so we have control over it
	}

	// events

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
		}
		else
		{
			m_pSelectFont->Enable(false);
			// revert the font back to the original
			m_pJournalTxtCtrl->SetFont(Fonts::GetDefaultFont(10));
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
		pResetConfigBtn->Bind(wxEVT_BUTTON, &AdvancedPagePanel::OnResetConfig, this);

		wxFlexGridSizer* pAdvancedSizer = new wxFlexGridSizer(2, wxSize(5, 1));

		pTopSizer->Add(pDesc, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
		pTopSizer->Add(pAdvancedSizer, wxSizerFlags().Expand());
		pAdvancedSizer->Add(pResetConfigTxt, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
		pAdvancedSizer->Add(pResetConfigBtn, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
	}

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