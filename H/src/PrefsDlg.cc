#include <wx/msgdlg.h>
#include <wx/config.h>
#include <wx/translation.h>
#include <wx/fontpicker.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include "PrefsDlg.h"
#include "Font/Font.hpp"

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
	ID_FONT_PICKER
};

class GeneralPagePanel : public wxPanel
{
private:
	wxCheckBox* m_pCheckCustomFont;
	wxFontPickerCtrl* m_pFontPicker;

public:
	GeneralPagePanel(wxWindow* parent)
		: wxPanel(parent)
	{
		wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
		this->SetSizerAndFit(pTopSizer);

		// =============== appearance ===============
		wxStaticText* pAppearanceText = new wxStaticText(this, wxID_STATIC, _("Appearance"));
		pAppearanceText->SetFont(Fonts::GetBoldFont(10));
		pTopSizer->Add(pAppearanceText, wxSizerFlags().CentreHorizontal().Left().Border(wxALL, 5));

		wxFlexGridSizer* pAppearanceSizer = new wxFlexGridSizer(2, wxSize(5, 1));
		pAppearanceSizer->AddGrowableCol(1);
		pTopSizer->Add(pAppearanceSizer, wxSizerFlags().Expand());

		m_pFontPicker = new wxFontPickerCtrl(this, (int)Prefs::ID_FONT_PICKER);
		m_pCheckCustomFont = new wxCheckBox(this, (int)Prefs::ID_CHECK_FONT, _("Use custom font in text fields:"));

		pAppearanceSizer->Add(m_pCheckCustomFont, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));
		pAppearanceSizer->Add(m_pFontPicker, wxSizerFlags().CentreVertical().Expand().Border(wxALL, 5));

		// Event binding
		m_pCheckCustomFont->Bind(wxEVT_CHECKBOX, &GeneralPagePanel::OnUseCustomFont, this);

		this->Fit();
		this->SetMinSize(wxSize(300, 350));
	}

private:
	void OnUseCustomFont(wxCommandEvent& event)
	{
#ifdef _DEBUG
		if (event.IsChecked())
			wxMessageBox(_("Custom font checked."));
#endif
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