#ifndef _LISTBOOK_H_
#define _LISTBOOK_H_

#include <wx/listbook.h>
#include <wx/bitmap.h>

class Listbook: public wxListbook
{
private:


public:
	Listbook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif