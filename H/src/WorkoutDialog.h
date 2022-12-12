#ifndef _WORKOUTDIALOG_H_
#define _WORKOUTDIALOG_H_

#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>

#define WD_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )
#define WD_SIZE	 ( wxSize(300, 250) )

class WorkoutDialog: public wxDialog
{
private:
	DECLARE_EVENT_TABLE()

private:
	// Visuals
	wxImageList* m_pImageList;
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

	// 

public:
	WorkoutDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = WD_STYLE);

	// Window setup
	void Init();
	void SetupWindowSizing();
	void SetupImageList();
	void SetupControls();
	void SetupSizers();

	// Events
};

#endif