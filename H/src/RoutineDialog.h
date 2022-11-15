#ifndef _ROUTINEDIALOG_H_
#define _ROUTINEDIALOG_H_

#include <wx/dialog.h>
#include <wx/arrstr.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/choice.h>
#include "EntryList.h"

#define RDLG_SIZE ( wxSize(250, 350) )
#define RDLG_MAX_SIZE ( wxSize(285, 365) )
#define RDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )

// Choice list size
#define CL_SIZE ( 7 )

class RoutineInfo
{
private:
	int m_index;
	wxString m_choice;
};

class RoutineDialog: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	// the ctor will take an EC vec so we can add the correct items to a selection list
	std::vector<EntryContent> m_content;
	wxArrayString m_contentNames;

	wxArrayString m_choiceArray;
	wxChoice* m_pChoice[CL_SIZE];

	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pDaySizer; // This sizer will be re-initialised and recycled to format all the days in the week.

public:
	RoutineDialog(const std::vector<EntryContent>& content,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = RDLG_SIZE,
		long style = RDLG_STYLE);

	// Setup
	void Init();
	void RetrieveAllNames();
	void SetupSizing();
	void SetupControls();
	void CreateControls();

	// Events
	void OnOK(wxCommandEvent& WXUNUSED(event));
	void OnClose(wxCloseEvent& WXUNUSED(event));
};

#endif