#ifndef _WORKOUTWINDOW_H_
#define _WORKOUTWINDOW_H_

#include <wx/frame.h>
#include <wx/toolbar.h>
#include <wx/textctrl.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include "WPLists.h"
#include "SaveWorkoutDialog.h"

#define WD_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX )
#define WD_SIZE	 ( wxSize(525, 450) )

class WorkoutWindow: public wxFrame
{
private:
	// Visuals
	wxBitmap m_cutBmp;
	wxBitmap m_copyBmp;
	wxBitmap m_pasteBmp;
	wxBitmap m_undoBmp;
	wxBitmap m_redoBmp;
	wxBitmap m_saveBmp;
	wxBitmap m_exportBmp;

	// Controls
	wxToolBar* m_pToolBar;
	wxTextCtrl* m_pTextCtrl;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;

	// Validation & other
	wxString m_workoutContent;
	WorkoutList* m_pWorkoutList;
	SaveWorkoutDialog* m_pSaveWorkoutDlg;

public:
	WorkoutWindow(WorkoutList* pWorkoutList,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Create New Workout"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = WD_STYLE);
	~WorkoutWindow();

	// List actions
	__forceinline void AddToWorkoutList();
	void SaveToWorkoutList();
	void OpenWorkout(const wxString& content);

	// Get/set
	wxTextCtrl* GetTextCtrl() const { return m_pTextCtrl; }
	void SetTextFont(const wxFont& font) { m_pTextCtrl->SetFont(font); }

	// Window setup
	void Init();
	void LoadConfig();
	void SetupToolBar();
	void SetupWindowSizing();
	void SetupImages();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnCut(wxCommandEvent& event);
	void OnCopy(wxCommandEvent& event);
	void OnPaste(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnExport(wxCommandEvent& event);
};

#endif