#ifndef BUGREPORT_H
#define BUGREPORT_H

#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/bmpbuttn.h>
#include "PrefsDlg.h"

class BugReport : public wxDialog
{
public:
	BugReport(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~BugReport();
};

#endif