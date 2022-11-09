#ifndef _ENTRYLIST_H_
#define _ENTRYLIST_H_

#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/menu.h>
#include <vector>

#define LIST_STYLE ( wxLC_REPORT | wxLC_EDIT_LABELS )
#define EC_SIZE	   ( 365 )

struct EntryContent
{
	wxString m_name;
	wxString m_content;
};

class EntryList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pPopUpMenu;
	wxTextCtrl* m_pTextCtrl;

	wxImageList* m_pImageList;
	wxBitmap m_pencilBmp;

	wxListItem m_itemCol;
	
	std::vector<EntryContent> m_entryContent;
	wxString m_currentItemName;
	long m_selectionIndex;

public:
	EntryList(wxTextCtrl* pTextCtrl,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = LIST_STYLE);

	void AddItem(const wxString& name, const wxString& content);

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