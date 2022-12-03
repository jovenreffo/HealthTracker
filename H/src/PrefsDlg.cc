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

class GeneralPagePanel : public wxPanel
{
private:
	wxCheckBox* m_pCheckCustomFont;
	wxButton* m_pSelectFont;
	wxFontDialog* m_pFontDialog;
	wxTextCtrl* m_pJournalTxtCtrl;
	wxStaticText* m_pWhatFont;

	wxFont m_selectedFont;

public:
	GeneralPagePanel(wxWindow* parent)
		: wxPanel(parent)
	{
		this->SetupWindowPointers();
		wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
		this->SetSizerAndFit(pTopSizer);

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
		m_pWhatFont = new wxStaticText(this, wxID_STATIC, wxString(_("Current font: ")) << m_pCheckCustomFont->GetFont().GetFaceName() << _(" (default)"), wxDefaultPosition, wxDefaultSize);
		m_pWhatFont->SetForegroundColour(wxColour(128, 128, 128));

		pAppearanceSizer->Add(m_pCheckCustomFont, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pAppearanceSizer->Add(m_pSelectFont, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pAppearanceSizer->Add(m_pWhatFont, wxSizerFlags().CentreVertical().Expand().Border(wxLEFT, 5));

		// Event binding
		m_pCheckCustomFont->Bind(wxEVT_CHECKBOX, &GeneralPagePanel::OnUseCustomFont, this);
		m_pSelectFont->Bind(wxEVT_BUTTON, &GeneralPagePanel::OnFontSelect, this);
		m_pSelectFont->Bind(wxEVT_UPDATE_UI, &GeneralPagePanel::UpdateFontSelect, this);

		this->Fit();
		this->SetMinSize(wxSize(300, 350));
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
		m_pJournalTxtCtrl = wxDynamicCast(pMainWin, wxTextCtrl); // cast the window to a wxTextCtrl so we have control over it
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
				m_pJournalTxtCtrl->SetFont(m_selectedFont);
			m_pWhatFont->SetLabel(wxString(_("Current font: ")) << m_selectedFont.GetFaceName());
		}
	}

	void OnFontSelect(wxCommandEvent& event)
	{
		this->DoFontSelect();
	}

	void OnUseCustomFont(wxCommandEvent& event)
	{
		if (event.IsChecked())
		{
			m_pSelectFont->Enable(true);
			this->DoFontSelect();
		}
		else
		{
			m_pSelectFont->Enable(false);
			// revert the font back to the original
			m_pJournalTxtCtrl->SetFont(Fonts::GetDefaultFont(10));
		}
	}
};

class GeneralPage : public wxStockPreferencesPage
{
public:
	GeneralPage() : wxStockPreferencesPage(wxStockPreferencesPage::Kind::Kind_General)
	{
	}

	virtual wxWindow* CreateWindow(wxWindow* parent) override
	{
		return new GeneralPagePanel(parent);
	}
};

PrefsDlg::PrefsDlg(const wxString& title)
	: wxPreferencesEditor(title)
{
	this->AddPage(new GeneralPage());
	
}