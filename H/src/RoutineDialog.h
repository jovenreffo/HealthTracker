#ifndef _ROUTINEDIALOG_H_
#define _ROUTINEDIALOG_H_

#include <wx/dialog.h>
#include <wx/arrstr.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/bmpbuttn.h>
#include <wx/statline.h>
#include <wx/choice.h>

#include <vector>
#include <array>

#include "EntryList.h"
#include "WPLists.h"
#include "RoutineStruct/Routine.h"
#include "RoutineView.h"
#include "WorkoutWindow.h"
#include "ViewButton.h"

#define RDLG_SIZE ( wxSize(300, 460) )
#define RDLG_MAX_SIZE ( wxSize(285, 365) )
#define RDLG_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )

enum class RD
{
	ID_ROUTINE_NAME,
	ID_VIEW
};

class Choice : public wxChoice
{
private:
	int m_uniqueID;

public:
	Choice(int uniqueID,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos,
		const wxSize& size,
		const wxArrayString& choices,
		long style = 0L);
	~Choice();

	void OnChoice(wxCommandEvent& event);
};

class RoutineDialog: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	// the ctor will take an EC vec so we can add the correct items to a selection list
	std::vector<EntryContent> m_content;

	RoutineList* m_pRoutineList;
	wxArrayString m_choiceArray;
	wxArrayString m_daysOfWeek;
	Choice* m_pChoice[ROUTINE_LIST_SIZE];
	std::vector<Routine> m_routineInfo;
	Routine m_routine; // transfer from RoutineView

	WorkoutList* m_pWorkoutList;
	WorkoutWindow* m_pWorkoutWindow;

	int m_choiceValidate[ROUTINE_LIST_SIZE];
	std::array<ViewButton*, ROUTINE_LIST_SIZE> m_viewButtonArr; // One unique button for each day of the week
	wxButton* m_pOk;
	wxButton* m_pCancel;

	wxBoxSizer* m_pTopSizer;
	wxFlexGridSizer* m_pDayFlexSizer;

	wxTextCtrl* m_pTextCtrl;
	wxString m_routineName;

public:
	RoutineDialog(const std::vector<EntryContent>& content,
		WorkoutList* pWorkoutList,
		RoutineList* pRoutineList,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = RDLG_SIZE,
		long style = RDLG_STYLE);
	~RoutineDialog();

	// Getters
	const std::vector<Routine>& GetRoutineInfo() const { return m_routineInfo; }
	const wxString& GetRoutineName() const { return m_routineName; }
	const Routine& GetRoutine() const { return m_routine; }

	// Setup
	void Init();
	void CreateControls();
	void SetupSizing();
	void SetupControls();

	void OpenRoutine();
	void HandleExit();

	// Events
	void OnOK(wxCommandEvent& WXUNUSED(event));
	void OnClose(wxCloseEvent& WXUNUSED(event));
	void OnEnter(wxCommandEvent& WXUNUSED(event));
	void OnChoice(wxCommandEvent& WXUNUSED(event));
};

#endif