#ifndef _PREFSDLG_H_
#define _PREFSDLG_H_

#include <wx/preferences.h>
#include <wx/dialog.h>

class PrefsDlg : public wxPreferencesEditor
{
public:
	PrefsDlg(const wxString& title);
};

#endif