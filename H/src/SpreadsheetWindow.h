#ifndef SPREADSHEETWINDOW_H
#define SPREADSHEETWINDOW_H

#include <wx/grid.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/dialog.h>
#include <wx/wx.h>

// Spreadsheet window style and size macros
#define SSW_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX )
#define SSW_SIZE ( wxSize(440, 280) )

class AddTableDlg : public wxDialog
{
private:
	wxString m_whichStr;

	// Controls
	wxSpinCtrl* m_pNumCtrl;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pCtrlSizer; //wxHORIZONTAL
	wxBoxSizer* m_pButtonSizer; //wxHORIZONTAL

	// Validator
	int m_num;

public:
	AddTableDlg(const wxString& which,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~AddTableDlg();

	void BindEvents();

	// Getter
	const int GetNum() const { return m_num; }

	// Init
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

enum class SSW
{
	ID_EXPORT_PDF,
	ID_INSERT_ROW,
	ID_INSERT_COL,
	ID_RESET_TABLE,
	ID_RESET_TABLE_SIZE
};

class ExerciseGrid;

class SpreadsheetWindow : public wxFrame
{
private:
	wxMenu* m_pFileMenu; wxMenu* m_pExportSubMenu;
	wxMenu* m_pInsertMenu;
	wxMenu* m_pEditMenu;
	wxMenuBar* m_pMenuBar;
	ExerciseGrid* m_pGrid;
	AddTableDlg* m_pAddTableDlg;

	wxBoxSizer* m_pTopSizer;

public:
	SpreadsheetWindow(wxWindow* parent,
		wxWindowID id = -1,
		const wxString& title = _T("Spreadsheet"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = SSW_SIZE,
		long style = SSW_STYLE);
	~SpreadsheetWindow();

	// Window setup
	bool Create(wxWindow* parent,
		wxWindowID id = -1,
		const wxString& title = _T("Spreadsheet"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = SSW_SIZE,
		long style = SSW_STYLE);

	void Init();
	void SetupMenu();
	void SetupSizing();
	void SetupControls();
	void SetupSizers();
	void BindEvents();

	// Events
	void OnExit(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnExportPDF(wxCommandEvent& event);

	void OnAddRow(wxCommandEvent& event);
	void OnAddCol(wxCommandEvent& event);

	void OnResetTablePosition(wxCommandEvent& event);
	void OnResetTableSize(wxCommandEvent& event);
};

class ExerciseGrid: public wxGrid
{
private:
	wxFont m_cellFont;

public:
	ExerciseGrid(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxWANTS_CHARS);

	// general grid functionality
	void ResetTablePosition();
	void ResetTableSize();

	// init
	void Init();
	void SetupConfig();

	// init workout template
	void SetupWorkoutTemplate();
	void SetupTitle();
	void SetupDayLabel();
	void SetupMuscleGroups();
};

#endif