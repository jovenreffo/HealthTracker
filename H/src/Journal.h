#ifndef _JOURNAL_H_
#define _JOURNAL_H_

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include "EntryList.h"

enum
{
	ID_SAVE = 50,
	ID_EXPORT
};

class Journal: public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxBoxSizer* m_pTopSizer; // vertical
	wxBoxSizer* m_pButtonSizer;

	wxStaticText* m_pDateText;
	wxStaticText* m_pMessageText;
	wxStaticText* m_pPrevEntryText;

	wxTextCtrl* m_pTextCtrl;
	EntryList* m_pEntryList;

	wxButton* m_pSaveButton;
	wxButton* m_pExportButton;

public:
	Journal(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Panel setup
	void Init();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnSaveToEntries(wxCommandEvent& event);
	void OnExport(wxCommandEvent& event);
};

#endif