#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/menu.h>
#include <vector>

#define LIST_STYLE ( wxLC_REPORT | wxLC_EDIT_LABELS )
#define EC_SIZE	   ( 365 )

class EntryContent
{
private:
	wxString m_name;
	wxString m_content;

public:
	EntryContent(const wxString& name, const wxString& content)
		: m_name{ name }, m_content{ content }
	{
	}

	const wxString& GetName() const { return m_name; }
	const wxString& GetContent() const { return m_content; }

	void SetName(const wxString& name) { m_name = name; }
	void SetContent(const wxString& content) { m_content = content; }
};

class EntryList: public wxListView
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenu* m_pPopUpMenu;
	wxMenu* m_pPopUpMenuCol;
	wxTextCtrl* m_pTextCtrl;

	wxImageList* m_pImageList;
	wxBitmap m_pencilBmp;

	wxListItem m_itemCol;
	
	std::vector<EntryContent> m_entryContent;
	wxString m_currentItemName;
	long m_selectionIndex;

	// Config
	int m_numEntries;

public:
	EntryList(int* pNumEntries,
		wxTextCtrl* pTextCtrl,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = LIST_STYLE);

	void AddItem(const wxString& name, const wxString& content);
	void OpenEntry();

	// Initialization
	void Init();
	void SetupPopUpMenu();
	void SetupBitmaps();
	void SetupList();

	void ResetList();
	void HandleDeleteItem();

	// Events
	void OnRightClickTitle(wxListEvent& event);
	void OnRightClick(wxListEvent& event);
	void OnDoubleClick(wxListEvent& event);
	void OnItemSelected(wxListEvent& event);
	void OnOpenEntry(wxCommandEvent& event);
	void OnRemoveEntry(wxCommandEvent& event);
	void OnClearEntryList(wxCommandEvent& event);
	void OnKey(wxKeyEvent& event);
};

#endif