#ifndef _ABOUTDIALOG_H_
#define _ABOUTDIALOG_H_

#include <wx/aboutdlg.h>
#include <wx/dialog.h>
#include <wx/html/htmlwin.h>
#include <wx/wxhtml.h>

#define AD_SIZE (wxSize(400, 375))

class AboutDialog: public wxDialog
{
private:
	wxAboutDialogInfo m_info;
	wxArrayString m_developers;

public:
	AboutDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("About"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = AD_SIZE,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);

	void SetupSizing();

	// events
	void OnOK(wxCommandEvent& event);
	void OnLinkClicked(wxHtmlLinkEvent& link);
};

#endif