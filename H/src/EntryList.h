#ifndef _ENTRYLIST_H_
#define _ENTRYLIST_H_

#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/menu.h>

#define LIST_STYLE (wxLC_REPORT | wxLC_EDIT_LABELS)

class EntryList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pPopUpMenu;

	wxImageList* m_pImageList;
	wxBitmap m_pencilBmp;

	wxListItem m_itemCol;

	wxString m_currentItemName;
	long m_selectionIndex;

public:
	EntryList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = LIST_STYLE);

	// Initialization
	void Init();
	void SetupPopUpMenu();
	void SetupBitmaps();
	void SetupList();

	// Events
	void OnRightClick(wxListEvent& event);
	void OnItemSelected(wxListEvent& event);
	void OnOpenEntry(wxCommandEvent& event);
	void OnRemoveEntry(wxCommandEvent& event);
};

#endif