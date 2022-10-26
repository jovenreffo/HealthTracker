#ifndef _LISTBOOK_H_
#define _LISTBOOK_H_

#include <wx/listbook.h>
#include <wx/bitmap.h>

#include "Journal.h"

class Listbook: public wxListbook
{
private:
	// Tabs
	Journal* m_pJournal;

public:
	Listbook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Setup
	void SetupTabs();
};

#endif