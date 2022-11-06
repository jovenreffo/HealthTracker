#ifndef _WORKOUTWINDOW_H_
#define _WORKOUTWINDOW_H_


#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/fontdlg.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/button.h>

#include "SaveWorkoutDialog/SaveWorkoutDialog.h"
#include "WPLists/WPLists.h"

#define WORKOUT_WINDOW_SIZE (wxSize(670, 500))
#define WORKOUT_WINDOW_STYLE (wxDEFAULT_FRAME_STYLE)

enum
{
	ID_CUT = 75,
	ID_COPY,
	ID_PASTE,
	ID_SELECT_ALL,
	ID_UNDO,
	ID_REDO,
	ID_ZOOMIN,
	ID_ZOOMOUT,
	ID_OPEN,
	ID_SAVE,
	ID_SAVEAS,
	ID_STW,
	ID_CLEAR_TEXT,
	ID_CHANGE_FONT,
	ID_FULLSCREEN
};

class WorkoutWindow : public wxFrame
{
	DECLARE_EVENT_TABLE()

private:
	int m_nFontSize;

	bool m_bActiveFile{ false };
	bool m_bFileSaved{ false };

	wxWindow* m_pParent;
	WorkoutList* m_pWorkoutList;

	wxString m_currentFileName;
	wxString m_currentFilePath;
	wxString m_saveFilePath;

	wxBoxSizer* m_topSizer;
	wxBoxSizer* m_buttonSizer;

	wxTextCtrl* m_pTextBox;
	wxButton* m_clearButton;
	wxButton* m_fontButton;
	wxButton* m_stwButton; // save to workouts button

	wxToolBar* m_pToolBar;
	wxMenuBar* m_pMenuBar;
	wxMenu* m_pFileMenu;
	wxMenu* m_pEditMenu;
	wxMenu* m_pViewMenu;

	wxBitmap m_cutBmp;
	wxBitmap m_copyBmp;
	wxBitmap m_pasteBmp;
	wxBitmap m_undoBmp;
	wxBitmap m_redoBmp;
	wxBitmap m_zoomInBmp;
	wxBitmap m_zoomOutBmp;
	wxBitmap m_openBmp;
	wxBitmap m_saveBmp;
	wxBitmap m_saveAsBmp;

	wxFontDialog* m_pFontDialog;

	SaveWorkoutDialog* m_pSaveWorkoutDlg;
	wxString m_workoutName;

public:
	WorkoutWindow(wxWindow* parent, wxWindowID id, WorkoutList* pWorkoutList);

	// Window functions
	void Init();
	void SetupBitmaps();
	void SetupToolBar();
	void SetupMenuBar();
	void SetupControls();
	void SetupSizers();

	void ZoomIn();
	void ZoomOut();

	const wxString GetWorkoutName() const { return m_workoutName; }
	void AddItemToWorkoutList();

	// Events
	void OnSTW(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnFullScreen(wxCommandEvent& event);
	void OnDropFile(wxDropFilesEvent& event);
	void OnMouse(wxMouseEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnText(wxCommandEvent& event);
	void OnClearText(wxCommandEvent& event);
	void OnChangeFont(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnCut(wxCommandEvent& event);
	void OnCopy(wxCommandEvent& event);
	void OnPaste(wxCommandEvent& event);
	void OnSelectAll(wxCommandEvent& event);
	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);
	void OnZoomIn(wxCommandEvent& event);
	void OnZoomOut(wxCommandEvent& event);
};

#endif