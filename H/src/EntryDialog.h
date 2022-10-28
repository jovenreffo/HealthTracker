#ifndef _ENTRYDIALOG_H_
#define _ENTRYDIALOG_H_

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/statline.h>

#define ENTRY_DIALOG_STYLE (wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX)

class EntryDialog: public wxDialog
{
public:
	EntryDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = ENTRY_DIALOG_STYLE);
};

#endif