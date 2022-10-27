#ifndef _ENTRYLIST_H_
#define _ENTRYLIST_H_

#include <wx/listctrl.h>
#include <wx/imaglist.h>

#define LIST_STYLE (wxLC_REPORT | wxLC_EDIT_LABELS)

class EntryList: public wxListView
{
private:
	wxImageList* m_pImageList;
	wxBitmap m_pencilBmp;

	wxListItem m_itemCol;

public:
	EntryList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = LIST_STYLE);

	// Initialization
	void Init();
	void SetupBitmaps();
	void SetupList();
};

#endif