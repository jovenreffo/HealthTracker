#ifndef SPREADSHEETWINDOW_H
#define SPREADSHEETWINDOW_H

#include <wx/grid.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/dialog.h>
#include <wx/wx.h>
#include <wx/clrpicker.h>
#include <wx/fontpicker.h>
#include <wx/fontdlg.h>
#include <wx/toolbar.h>

#include <vector>
#include "GridCommand.h"

// Spreadsheet window style and size macros
#define SSW_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX )
#define SSW_SIZE ( wxSize(850, 600) )

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

class DeleteElementsDlg : public wxDialog
{
private:
	wxString m_whichStr;

	// Controls
	wxSpinCtrl* m_pNumCtrl;
	wxButton* m_pOk;
	wxButton* m_pCancel;
	wxCheckBox* m_pCheckBox;

	wxGrid* m_pGrid;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxFlexGridSizer* m_pCtrlSizer;
	wxBoxSizer* m_pButtonSizer; //wxHORIZONTAL

	// Validator
	int m_num;
	bool m_bRemoveFromFront{ false };

public:
	DeleteElementsDlg(wxGrid* pGrid,
		const wxString& which,
		wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~DeleteElementsDlg();

	// Getter
	const int GetNum() const { return m_num; }
	const bool IsFrontChecked() const { return m_bRemoveFromFront; }

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

class ChangeCellFontDlg : public wxDialog
{
private:
	// Controls
	wxSpinCtrl* m_pRowSpin;
	wxSpinCtrl* m_pColSpin;
	wxFontPickerCtrl* m_pFontPicker;

	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pCtrlSizer;

	// Validators
	int m_row;
	int m_col;
	wxFont m_font;

public:
	ChangeCellFontDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~ChangeCellFontDlg();

	// Getters
	const int GetRow() const { return m_row; }
	const int GetCol() const { return m_col; }
	const wxFont& GetFont() const { return m_font; }
	const wxFontPickerCtrl* GetPickerCtrl() const { return m_pFontPicker; }

	// Init
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnSelectFont(wxFontPickerEvent& event);
};

class ChangeCellSizeDlg : public wxDialog
{
private:
	// Controls
	wxSpinCtrl* m_pRow;
	wxSpinCtrl* m_pCol;
	wxSpinCtrl* m_pNumRows; // the number of rows the new cell will occupy
	wxSpinCtrl* m_pNumCols; // the number of cols the new cell will occupy
	// Validators
	int m_row;
	int m_col;
	int m_numRows;
	int m_numCols;

	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pControlSizer;

public:
	ChangeCellSizeDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Change Cell Size"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~ChangeCellSizeDlg();

	// Getters
	const int GetRow() const { return m_row; }
	const int GetCol() const { return m_col; }
	const int GetNumRows() const { return m_numRows; }
	const int GetNumCols() const { return m_numCols; }

	// Setters for spin controls
	void SetRow(int r) { m_pRow->SetValue(r); }
	void SetCol(int c) { m_pCol->SetValue(c); }

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();
	void ToolTips();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
};


// ===== AddWorkoutDayDlg =====

class AddWorkoutDayDlg : public wxDialog
{
private:
	// Controls
	wxSpinCtrl* m_pNumCtrl;
	wxButton* m_pOk;
	wxButton* m_pCancel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pControlSizer;

	// Validation
	int m_numDays;

public:
	AddWorkoutDayDlg(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Add Workout Day"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~AddWorkoutDayDlg();

	// Getters
	const int GetNumDays() const { return m_numDays; }

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();
	void SetupSizing();
	void ToolTip();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnExceedLimit(wxCommandEvent& event);
};

// ===== SSWToolBar =====

enum class SSWTB
{
	ID_CHANGE_FONT,
	ID_SET_FILL
};

// class for storing info about the cell for actions: cut, copy, paste
class CellInfo
{
private:
	wxColour m_bgColour;
	wxString m_cellText;
	wxFont m_cellFont;

public:
	CellInfo(const wxColour& bgColour, const wxString& cellText, const wxFont& cellFont)
		: m_bgColour{ bgColour }, m_cellText{ cellText }, m_cellFont{ cellFont }
	{ }

	// Getters
	const wxColour& GetBackgroundColour() const { return m_bgColour; }
	const wxString& GetCellText() const { return m_cellText; }
	const wxFont& GetCellFont() const { return m_cellFont; }
};

class ExerciseGrid;

class SSWToolBar : public wxToolBar
{  
private:
	// Grid needed for modifications
	ExerciseGrid* m_pExerciseGrid;
	wxGridCellCoords m_selectedCell;

	// Cell info for cutting/copying/pasting
	//CellInfo m_selectedCellInfo;
	GridCellState m_currCellState;


	// Bitmaps
	wxBitmap m_undoBmp;
	wxBitmap m_redoBmp;

	wxBitmap m_cutBmp;
	wxBitmap m_copyBmp;
	wxBitmap m_pasteBmp;

	wxBitmap m_fontBmp;
	wxBitmap m_fillBmp;

public:
	SSWToolBar(ExerciseGrid* pExerciseGrid,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTB_DEFAULT_STYLE);
	~SSWToolBar();

	// Setup
	void Init();
	void SetupBitmaps();
	void SetupTools();

	// Events
	void BindEvents();
	void UnbindEvents();

	void OnUndo(wxCommandEvent& event);
	void OnRedo(wxCommandEvent& event);

	void OnCut(wxCommandEvent& event);
	void OnCopy(wxCommandEvent& event);
	void OnPaste(wxCommandEvent& event);

	void OnChangeFont(wxCommandEvent& event);
	void OnSetFill(wxCommandEvent& event);
};

enum class SSW
{
	ID_EXPORT_PDF,
	ID_INSERT_ROW,
	ID_INSERT_COL,
	ID_INSERT_DAY,
	ID_RESET_TABLE_POS,
	ID_RESET_TABLE_SIZE,
	ID_RESET_GRID_DIMENSIONS,
	ID_RESET_TABLE_LAYOUT,
	ID_CLEAR_TABLE_CONFIG,
	ID_CHANGE_CELL_BG_COLOUR,
	ID_CHANGE_CELL_FONT,
	ID_CHANGE_CELL_SIZE,
	ID_DELETE_ROW,
	ID_DELETE_COL
};

class SpreadsheetWindow : public wxFrame
{
private:
	// Menu
	wxMenu* m_pFileMenu; wxMenu* m_pExportSubMenu;
	wxMenu* m_pInsertMenu;
	wxMenu* m_pEditMenu; wxMenu* m_pResetSubMenu; wxMenu* m_pModifySubMenu; wxMenu* m_pEditDeleteMenu;
	wxMenuBar* m_pMenuBar;

	// Toolbar 
	SSWToolBar* m_pToolBar;

	// Grid stuff
	ExerciseGrid* m_pGrid;

	// Control + dlg members
	AddTableDlg* m_pAddTableDlg;
	AddWorkoutDayDlg* m_pAddWorkoutDayDlg;
	CCBD* m_pCCBD;
	ChangeCellFontDlg* m_pCCFD;
	ChangeCellSizeDlg* m_pCCSD;
	DeleteElementsDlg* m_pDeleteElemsDlg;

	// Sizers
	wxBoxSizer* m_pTopSizer;

	// Config stuff
	int m_numRows;
	int m_numCols;
	std::vector<GridCellState> m_gridState;

public:
	SpreadsheetWindow(wxWindow* parent,
		wxWindowID id = -1,
		const wxString& title = _T("Spreadsheet"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = SSW_SIZE,
		long style = SSW_STYLE);
	~SpreadsheetWindow();

	// Config
	void LoadConfig();
	void SaveConfig();

	// Window setup
	bool Create(wxWindow* parent,
		wxWindowID id = -1,
		const wxString& title = _T("Spreadsheet"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = SSW_SIZE,
		long style = SSW_STYLE);

	void Init();
	void SetupMenu();
	void SetupToolBar();
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
	void OnInsertDay(wxCommandEvent& event);

	void OnResetTablePosition(wxCommandEvent& event);
	void OnResetTableSize(wxCommandEvent& event);
	void OnResetTableLayout(wxCommandEvent& event);
	void OnClearTableConfiguration(wxCommandEvent& event);

	void OnChangeBackgroundColour(wxCommandEvent& event);
	void OnChangeCellFont(wxCommandEvent& event);
	void OnChangeCellSize(wxCommandEvent& event);

	void OnDeleteRows(wxCommandEvent& event);
	void OnDeleteCols(wxCommandEvent& event);
};

class ExerciseGrid : public wxGrid
{
private:
	wxMenu* m_pPopupMenu;
	wxMenu* m_pEditCellSub;

	wxFontDialog* m_pFontDlg;
	ChangeCellSizeDlg* m_pCCSD;

	wxFont m_cellFont;

	wxArrayString m_labels;
	wxGridCellCoords m_currCell;

	GridCellState m_currCellState;

	int m_currDay;
	int m_rowDayCoord; // value for writing the day number in a certain row
	
	// Load from config
	int m_numRows;
	int m_numCols;

public:
	ExerciseGrid(int rows,
		int cols,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxWANTS_CHARS);
	~ExerciseGrid();

	// getters
	const GridCellState GetSelectedCellState() const { return m_currCellState; }
	const wxGridCellCoords GetSelectedCell() const { return m_currCell; }

	// general grid functionality
	void ResetTablePosition();
	void ResetTableSize(); // resets CELL size

	// init
	void Init();
	void SetupConfig();
	void SetupMenu();
	void SetupLabelArray();

	// init workout template
	void SetupWorkoutTemplate();
	void AddWorkoutDay();
	void SetupTitle();
	void SetupDayLabel();

	// events
	void OnUpdateCell(wxGridEvent& event);
	void OnLeftClickCell(wxGridEvent& event);
	void OnSelectCell(wxGridEvent& event);
	void OnRightClickCell(wxGridEvent& event);
	void OnChangeBackgroundColour(wxCommandEvent& event);
	void OnChangeCellFont(wxCommandEvent& event);
	void OnChangeCellSize(wxCommandEvent& event);
};

#endif