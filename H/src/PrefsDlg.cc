#include <wx/config.h>
#include <wx/translation.h>
#include "PrefsDlg.h"

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

class GeneralPagePanel : public wxPanel
{
public:
	GeneralPagePanel(wxWindow* parent)
		: wxPanel(parent)
	{

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