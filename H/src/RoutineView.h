#ifndef _ROUTINEVIEW_H_
#define _ROUTINEVIEW_H_

/* The RoutineView class will be structurally similar to routine dialog.
*  This alternative was developed with the intention of avoiding circular dependencies and use of global variables.
*  It also incorporates some new functionality, which the normal dialog should not contain.
*/

#include <wx/dialog.h>
#include <wx/arrstr.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/bmpbuttn.h>
#include <wx/statline.h>
#include <wx/choice.h>
#include "EntryList.h"
#include "RoutineStruct/Routine.h"

#define RVDLG_SIZE ( wxSize(250, 350) )
#define RVDLG_MAX_SIZE ( wxSize(285, 365) )
#define RVDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )

class RoutineView: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	std::vector<EntryContent> m_content;
	std::vector<Routine> m_routineInfo;

	wxBitmap m_viewBmp;
	wxBitmapButton* m_pViewButton;

	wxArrayString m_choiceArray;
	wxChoice* m_pChoice[CL_SIZE];

	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxBoxSizer* m_pTopSizer;
	wxFlexGridSizer* m_pDayFlexSizer;

	wxTextCtrl* m_pTextCtrl;

public:
	RoutineView(const std::vector<Routine>& routineInfo,
		const std::vector<EntryContent>& content,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = RVDLG_SIZE,
		long style = RVDLG_STYLE);

	// Setup
	void Init();
	void SetupSizing();
	void SetupControls();
	void CreateControls();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};

#endif