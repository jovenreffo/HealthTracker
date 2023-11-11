#ifndef CLIENTPANEL_H
#define CLIENTPANEL_H

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/font.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/bmpbuttn.h>
#include <wx/timectrl.h>

#include <vector>
#include <array>
#include <utility>

#include "WorkoutWindow.h"

class ClientPair
{
private:
	int m_dayIndex;
	wxDateTime m_dateTime;
	wxString m_sWorkout; // the workout for the selected day(s)
	bool m_bChecked;

public:
	ClientPair(int dayIndex, wxDateTime dateTime, bool bChecked)
		: m_dayIndex{ dayIndex }, m_dateTime{ dateTime }, m_bChecked{ bChecked }
	{ }

	// Getters
	const int GetDayIndex() const { return m_dayIndex; }
	const wxDateTime GetTime() const { return m_dateTime; }
};

// class for storing information about the client
class ClientInfo
{
private:
	wxString m_clientName;
	int m_sessionsPerWeek;

public:
	ClientInfo(const wxString& clientName, int sessions)
		: m_clientName{ clientName }, m_sessionsPerWeek{ sessions }
	{
	}

	// Getters
	const wxString& GetClientName()	const { return m_clientName; }
	const int GetNumSessions() const { return m_sessionsPerWeek; }

	// Setters
	void SetClientName(const wxString& name) { m_clientName = name; }
	void SetNumSessions(const int num) { m_sessionsPerWeek = num; }
};

class ClientSchedule : public wxListView
{
private:
	// List
	wxArrayString m_daysOfWeekStr;
	wxFont m_font;

	// Menu
	wxMenu* m_pMenu;

	// Image list
	wxImageList* m_pImageList;

public:
	ClientSchedule(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_EDIT_LABELS);
	~ClientSchedule();

	// Setup
	void SetupList();
	void SetupColumns();
	void SetupImageList();
	void SetupMenu();
	void SetListFont();

	// Actions & events
	void AddItem(const wxArrayString& workoutNames, const std::vector<ClientPair>& data);
	void RemoveItem(int index);

	void OnRightClickItem(wxListEvent& event);
};

class WorkoutListWindowSmall : public wxDialog
{
private:
	// members
	WorkoutList* m_pWorkoutList;
	WorkoutWindow* m_pWorkoutWin;

	wxButton* m_pOk;
	wxButton* m_pCancel;

	// sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;

	// validation
	int m_selectionIndex; // put the value of the selected index of the list in this variable
	wxString m_selectionStr;

public:
	WorkoutListWindowSmall(wxWindow* parent, WorkoutList* pWorkoutList);
	~WorkoutListWindowSmall();

	// control setup
	void SetupWorkoutListWindowSmall();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// getters
	const int GetSelectionIndex() const { return m_selectionIndex; }
	const wxString& GetSelectedName() const { return m_selectionStr; }

	// events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

// enum for listing different IDs, used to identify which button was pressed
enum class button_t : int
{
	ID_SUN = 0,
	ID_MON,
	ID_TUE,
	ID_WED,
	ID_THU,
	ID_FRI,
	ID_SAT
};

class NewClientDlg : public wxDialog
{
private:
	// Controls
	wxTextCtrl* m_pClientNameTxt;
	wxSpinCtrl* m_pNumSessionsCtrl;
	wxButton* m_pOk;
	wxButton* m_pCancel;
	
	// Days of week
	wxArrayString m_daysOfWeekStr;
	std::vector<wxCheckBox*> m_pDaysCheck;
	std::vector<wxBitmapButton*> m_pAddWorkoutBtn;
	std::vector<wxStaticText*> m_pWorkoutSelections;
	WorkoutList* m_pWorkoutList;
	WorkoutListWindowSmall* m_pWLWSmall;
	button_t btn_t;
	// array for holding and displaying workoutnames in statictext instances
	wxArrayString m_workoutNames; // for when the dialog returns wxID_OK

	// Session times
	std::vector<wxTimePickerCtrl*> m_pTimes;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pControlSizer;
	wxFlexGridSizer* m_pDayTimeSizer;

	// Validators
	wxString m_clientName;
	int m_numSessions;

public:
	NewClientDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Add New Client"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~NewClientDlg();

	// Getters
	const wxString& GetClientName() const { return m_clientName; }
	const int GetNumSessions() const { return m_numSessions; }
	const std::vector<wxCheckBox*>& GetDaysChecked() const { return m_pDaysCheck; }
	const std::vector<ClientPair>& FillClientSessionData(std::vector<ClientPair>& vec); // Only to be called after ShowModal() returns wxID_OK
	const wxArrayString& GetWorkoutNames() const { return m_workoutNames; }

	// Setup
	void SetupNewClientDlg();
	void SetupDaysArray();
	void SetupWorkoutBtns();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events
	void OnAddWorkout(wxCommandEvent& event);
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

class ClientList : public wxListView
{
private:
	wxFont m_font; // The font used for items in the list will be bigger, and slightly bolded.

	// Controls
	wxMenu* m_pMenu;
	wxImageList* m_pImageList;
	ClientSchedule* m_pClientSchedule; // Pass by pointer so an item can be deleted

	// Bitmaps, icons, images
	wxBitmap m_clientIconBmp;

public:
	ClientList(ClientSchedule* pClientSchedule,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_EDIT_LABELS);
	~ClientList();

	// Setup
	void SetupList();
	void SetupColumn();
	void SetupImageList();
	void SetupMenu();
	void SetListFont();
	
	// Actions & events
	void AddItem(const wxString& name, int sessions);

	void OnRightClickItem(wxListEvent& event);
	void OnRemoveClient(wxCommandEvent& event);
};

class ClientPanel : public wxPanel
{
private:
	// Controls
	wxButton* m_pAddClientBtn;
	ClientList* m_pClientList;
	ClientSchedule* m_pClientSchedule;
	NewClientDlg* m_pNewClientDlg;
	// Information from the dlg
	std::vector<ClientPair> m_clientInfoPairs;
	wxArrayString m_workoutNames; // for when the new client dialog returns wxID_OK

	// Splitter window for separating the client list and schedule
	wxPanel* m_pClientListPanel;
	wxPanel* m_pClientSchedPanel;
	wxSplitterWindow* m_pSplitterWin;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pClientListSizer;
	wxBoxSizer* m_pClientSchedSizer;
	wxBoxSizer* m_pTopButtonSizer;

	// Config
	int m_sashPosition;

public:
	ClientPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ClientPanel();
	
	// Config
	void SaveConfig();
	void LoadConfig();

	// Panel setup
	void InitClientPanel();
	void SetupClientListPanel();
	void SetupMemberControls();
	void SetupSplitterWin();
	void SetupSizers();

	// Events
	void OnAddClient(wxCommandEvent& event);
};

#endif