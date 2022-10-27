#ifndef _JOURNAL_H_
#define _JOURNAL_H_

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/listctrl.h>

class Journal : public wxPanel
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxBoxSizer* m_pTopSizer; // vertical
	wxBoxSizer* m_pDateSizer; // horizontal
	wxBoxSizer* m_pEntrySizer; // horizontal
	wxBoxSizer* m_pTextSizer; // vertical
	wxBoxSizer* m_pPrevEntrySizer; // vertical

	wxStaticText* m_pDateText;
	wxStaticText* m_pMessageText;
	wxStaticText* m_pPrevEntryText;

	wxTextCtrl* m_pTextCtrl;
	wxListCtrl* m_pListCtrl;

	wxButton* m_pSaveButton;

public:
	Journal(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	// Window setup


	// Events

};

#endif