#ifndef SPREADSHEETWINDOW_H
#define SPREADSHEETWINDOW_H

#include <wx/grid.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/dialog.h>
#include <wx/wx.h>
#include <wx/clrpicker.h>

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

class ChangeCellBackgroundDlg : public wxDialog
{
private:
	// Controls
	wxSpinCtrl* m_pRowSpin;
	wxSpinCtrl* m_pColSpin;
	wxColourPickerCtrl* m_pClrPicker;

	wxButton* m_pOk;
	wxButton* m_pCancel;
	
	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pCtrlSizer;

	// Validators
	int m_row;
	int m_col;
	wxColour m_colour;

public:
	ChangeCellBackgroundDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~ChangeCellBackgroundDlg();

	// Getters
	const int GetRow() const { return m_row; }
	const int GetCol() const { return m_col; }
	const wxColour& GetColour() const { return m_colour; }

	// Init
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};

// alias for the class so it's not a pain to type out
using CCBD = ChangeCellBackgroundDlg;

enum class SSW
{
	ID_EXPORT_PDF,
	ID_INSERT_ROW,
	ID_INSERT_COL,
	ID_RESET_TABLE,
	ID_RESET_TABLE_SIZE,
	ID_CHANGE_CELL_BG_COLOUR
};

class ExerciseGrid;

class SpreadsheetWindow : public wxFrame
{
private:
	wxMenu* m_pFileMenu; wxMenu* m_pExportSubMenu;
	wxMenu* m_pInsertMenu;
	wxMenu* m_pEditMenu; wxMenu* m_pResetSubMenu; wxMenu* m_pModifySubMenu;
	wxMenuBar* m_pMenuBar;
	ExerciseGrid* m_pGrid;
	AddTableDlg* m_pAddTableDlg;
	CCBD* m_pCCBD;

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

	void OnChangeBackgroundColour(wxCommandEvent& event);
	void OnChangeCellFont(wxCommandEvent& event);
};

class ExerciseGrid : public wxGrid
{
private:
	wxMenu* m_pPopupMenu;
	wxMenu* m_pEditCellSub;

	wxFont m_cellFont;

	wxArrayString m_labels;
	wxGridCellCoords m_currCell;

	int m_currDay{ 1 };
	int m_rowDayCoord{ 4 }; // value for writing the day number in a certain row

public:
	ExerciseGrid(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxWANTS_CHARS);
	~ExerciseGrid();

	// general grid functionality
	void ResetTablePosition();
	void ResetTableSize();

	// init
	void Init();
	void SetupConfig();
	void SetupMenu();
	void SetupLabelArray();

	// init workout template
	void SetupWorkoutTemplate();
	void SetupTitle();
	void SetupDayLabel();

	// events
	void OnSelectCell(wxGridEvent& event);
	void OnRightClickCell(wxGridEvent& event);
	void OnChangeBackgroundColour(wxCommandEvent& event);
};

#endif