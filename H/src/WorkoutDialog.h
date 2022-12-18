#ifndef _WORKOUTDIALOG_H_
#define _WORKOUTDIALOG_H_

#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include "WPLists.h"
#include "SaveWorkoutDialog.h"

#define WD_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX )
#define WD_SIZE	 ( wxSize(525, 450) )

class WorkoutDialog: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	// Visuals
	wxBitmap m_cutBmp;
	wxBitmap m_copyBmp;
	wxBitmap m_pasteBmp;
	wxBitmap m_undoBmp;
	wxBitmap m_redoBmp;
	wxBitmapButton* m_pCut;
	wxBitmapButton* m_pCopy;
	wxBitmapButton* m_pPaste;
	wxBitmapButton* m_pUndo;
	wxBitmapButton* m_pRedo;

	// Controls
	wxTextCtrl* m_pTextCtrl;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pTextActionSizer;
	wxBoxSizer* m_pButtonSizer;

	// Validation & other
	wxString m_workoutContent;
	WorkoutList* m_pWorkoutList;
	SaveWorkoutDialog* m_pSaveWorkoutDlg;

public:
	WorkoutDialog(WorkoutList* pWorkoutList,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Create New Workout"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = WD_STYLE);

	// List actions
	__forceinline void AddToWorkoutList();
	void SaveToWorkoutList();

	// Window setup
	void Init();
	void SetupWindowSizing();
	void SetupImages();
	void SetupControls();
	void SetupSizers();
	void BindEvents();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnCut(wxCommandEvent& event);
	void OnCopy(wxCommandEvent& event);
	void OnPaste(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);

};

#endif