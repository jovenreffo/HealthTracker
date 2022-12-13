#ifndef _WORKOUTDIALOG_H_
#define _WORKOUTDIALOG_H_

#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>

#define WD_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX )
#define WD_SIZE	 ( wxSize(525, 425) )

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
	void SetupImages();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

#endif