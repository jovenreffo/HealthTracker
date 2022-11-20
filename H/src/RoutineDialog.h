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
#include "WPLists.h"
#include "RoutineStruct/Routine.h"

#define RDLG_SIZE ( wxSize(250, 350) )
#define RDLG_MAX_SIZE ( wxSize(285, 365) )
#define RDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )

class RoutineDialog: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	// the ctor will take an EC vec so we can add the correct items to a selection list
	std::vector<EntryContent> m_content;
	wxArrayString m_contentNames;

	RoutineList* m_pRoutineList;
	wxArrayString m_choiceArray;
	wxChoice* m_pChoice[CL_SIZE];
	std::vector<Routine> m_routineInfo;

	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pDaySizer; // This sizer will be re-initialised and recycled to format all the days in the week.

	wxTextCtrl* m_pTextCtrl;
	wxString m_routineName;

public:
	RoutineDialog(const std::vector<EntryContent>& content,
		RoutineList* pRoutineList,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = RDLG_SIZE,
		long style = RDLG_STYLE);

	const std::vector<Routine>& GetRoutineInfo() const { return m_routineInfo; }
	const wxString& GetRoutineName() const { return m_routineName; }

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