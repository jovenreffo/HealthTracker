#ifndef JOURNAL_H
#define JOURNAL_H

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/listctrl.h>
#include <wx/button.h>

#include "aui_includes/aui_includes.h"
#include "EntryList.h"
#include "EntryDialog.h"
#include "EntryPair.h"

enum
{
	ID_SAVE_ENTRY = 50,
	ID_EXPORT,
	ID_ENTRY_TEXT
};

class Journal: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	bool m_bFileSaved{ false };

	wxString m_date;

	EntryDialog* m_pEntryDialog;

	wxBoxSizer* m_pTopSizer; // vertical
	wxBoxSizer* m_pButtonSizer;

	wxStaticText* m_pDateText;
	wxStaticText* m_pMessageText;
	wxStaticText* m_pPrevEntryText;

	wxTextCtrl* m_pTextCtrl;
	EntryList* m_pEntryList;

	wxButton* m_pSaveButton;
	wxButton* m_pExportButton;

	// AUI
	wxAuiManager m_auiMgr;
	wxString m_perspective; wxString m_defPerspective;
	wxPanel* m_pTextPanel; // this panel will contain the date, textctrl, and buttons
	wxPanel* m_pEntryPanel; // contains the entry list and m_pPrevEntryText

public:
	Journal(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~Journal();

	wxString GetDate();
	EntryList* GetEntryList() const { return m_pEntryList; }

	void ResetPerspective();

	// Panel setup
	void LoadConfig();
	void UpdateConfigPerspective();
	void SaveEntriesToConfig();
	void LoadEntriesFromConfig();
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupAUI();

	// Events
	void OnSaveToEntries(wxCommandEvent& event);
	void OnExport(wxCommandEvent& event);
};

#endif