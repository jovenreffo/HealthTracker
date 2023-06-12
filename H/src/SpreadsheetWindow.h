#ifndef SPREADSHEETWINDOW_H
#define SPREADSHEETWINDOW_H

#include <wx/grid.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/wx.h>

// Spreadsheet window style and size macros
#define SSW_STYLE ( wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX )
#define SSW_SIZE ( wxSize(440, 280) )

class ExerciseGrid;

class SpreadsheetWindow : public wxFrame
{
private:
	wxMenu* m_pFileMenu;
	wxMenuBar* m_pMenuBar;
	ExerciseGrid* m_pGrid;

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
	void SetupConfig();
	void BindEvents();

	// Events
	void OnExit(wxCommandEvent& event);
};

class ExerciseGrid: public wxGrid
{
public:
	ExerciseGrid(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxWANTS_CHARS);
};

#endif