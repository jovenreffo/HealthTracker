#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/stdpaths.h>
#include <wx/webview.h>

#include "AboutDialog.h"

AboutDialog::AboutDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	wxHtmlWindow* pHtmlWin;
	wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);

	pHtmlWin = new wxHtmlWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_DEFAULT_STYLE);
	pHtmlWin->SetBorders(0);
	pHtmlWin->LoadPage(wxStandardPaths::Get().GetDataDir() + _T("\\H\\src\\AboutDialog\\about.html"));
	pHtmlWin->SetInitialSize(wxSize(pHtmlWin->GetInternalRepresentation()->GetWidth(), pHtmlWin->GetInternalRepresentation()->GetHeight()));

	wxButton* pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);

	// add items to the sizer
	pTopSizer->Add(pHtmlWin, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 10));

#ifdef wxUSE_STATLINE
	pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 10));
#endif

	pTopSizer->Add(pOk, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));

	this->SetSizer(pTopSizer);
	pTopSizer->Fit(this);

	this->SetupSizing();

	// Connect events
	pOk->Bind(wxEVT_BUTTON, &AboutDialog::OnOK, this);
	pHtmlWin->Bind(wxEVT_HTML_LINK_CLICKED, &AboutDialog::OnLinkClicked, this);
}

void AboutDialog::SetupSizing()
{
	this->SetInitialSize(AD_SIZE);
	this->SetMinSize(AD_SIZE);
}

void AboutDialog::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void AboutDialog::OnLinkClicked(wxHtmlLinkEvent& event)
{
	if (event.GetLinkInfo().GetHref().StartsWith(_T("http://"))
		|| event.GetLinkInfo().GetHref().StartsWith(_T("https://")))
	{
		wxLaunchDefaultBrowser(event.GetLinkInfo().GetHref());
	}
}