#include "WorkoutWindow.h"
#include "StandardPath.hpp"
#include "xpm/xpm_include.h"

BEGIN_EVENT_TABLE(WorkoutWindow, wxFrame)
	EVT_DROP_FILES(WorkoutWindow::OnDropFile)
	EVT_CLOSE(WorkoutWindow::OnClose)
	EVT_TEXT(wxID_ANY, WorkoutWindow::OnText)
	EVT_BUTTON(ID_STW, WorkoutWindow::OnSTW)
	EVT_BUTTON(ID_CLEAR_TEXT, WorkoutWindow::OnClearText)
	EVT_BUTTON(ID_CHANGE_FONT, WorkoutWindow::OnChangeFont)
	// Menu events
	EVT_MENU(ID_FULLSCREEN, WorkoutWindow::OnFullScreen)
	EVT_MENU(wxID_EXIT, WorkoutWindow::OnExit)
	EVT_MENU(ID_CUT, WorkoutWindow::OnCut)
	EVT_MENU(ID_COPY, WorkoutWindow::OnCopy)
	EVT_MENU(ID_PASTE, WorkoutWindow::OnPaste)
	EVT_MENU(ID_SELECT_ALL, WorkoutWindow::OnSelectAll)
	EVT_MENU(ID_UNDO, WorkoutWindow::OnUndo)
	EVT_MENU(ID_REDO, WorkoutWindow::OnRedo)
	EVT_MENU(ID_ZOOMIN, WorkoutWindow::OnZoomIn)
	EVT_MENU(ID_ZOOMOUT, WorkoutWindow::OnZoomOut)
	EVT_MENU(ID_OPEN, WorkoutWindow::OnOpen)
	EVT_MENU(ID_SAVE, WorkoutWindow::OnSave)
	EVT_MENU(ID_SAVEAS, WorkoutWindow::OnSaveAs)
	// Tool events
	EVT_TOOL(ID_CUT, WorkoutWindow::OnCut)
	EVT_TOOL(ID_COPY, WorkoutWindow::OnCopy)
	EVT_TOOL(ID_PASTE, WorkoutWindow::OnPaste)
	EVT_TOOL(ID_UNDO, WorkoutWindow::OnUndo)
	EVT_TOOL(ID_REDO, WorkoutWindow::OnRedo)
	EVT_TOOL(ID_ZOOMIN, WorkoutWindow::OnZoomIn)
	EVT_TOOL(ID_ZOOMOUT, WorkoutWindow::OnZoomOut)
	EVT_TOOL(ID_OPEN, WorkoutWindow::OnOpen)
	EVT_TOOL(ID_SAVE, WorkoutWindow::OnSave)
	EVT_TOOL(ID_SAVEAS, WorkoutWindow::OnSaveAs)
END_EVENT_TABLE()

WorkoutWindow::WorkoutWindow(wxWindow* parent, wxWindowID id, WorkoutList* pWorkoutList)
	: wxFrame(parent, wxID_ANY, _T("Create Workout"), wxDefaultPosition, WORKOUT_WINDOW_SIZE, WORKOUT_WINDOW_STYLE),
	m_pParent{ parent }, m_pWorkoutList{ pWorkoutList }
{
	this->Init();
	this->SetMinSize(WORKOUT_WINDOW_SIZE);
}

void WorkoutWindow::Init()
{
	this->SetupBitmaps();
	this->SetupIcon();
	this->SetupToolBar();
	this->SetupMenuBar();
	this->SetupControls();
	this->SetupSizers();
}

void WorkoutWindow::SetupBitmaps()
{
	m_cutBmp = wxBitmap(cut_xpm);
	m_copyBmp = wxBitmap(copy_xpm);
	m_pasteBmp = wxBitmap(paste_xpm);
	m_undoBmp = wxBitmap(undo_xpm);
	m_redoBmp = wxBitmap(redo_xpm);
	m_zoomInBmp = wxBitmap(zoomin_xpm);
	m_zoomOutBmp = wxBitmap(zoomout_xpm);
	m_openBmp = wxBitmap(open_xpm);
	m_saveBmp = wxBitmap(save_xpm);
	m_saveAsBmp = wxBitmap(saveas_xpm);
}

void WorkoutWindow::SetupIcon()
{
	m_programIcon = wxIcon(path_data::dataDir + _T("\\Images\\workout.png"), wxBITMAP_TYPE_PNG);
	this->SetIcon(m_programIcon);
}

void WorkoutWindow::SetupToolBar()
{
	m_pToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT);

	// Add tools
	m_pToolBar->AddTool(ID_OPEN, _T("Open"), m_openBmp, _T("Open a text file."));
	m_pToolBar->AddTool(ID_SAVE, _T("Save"), m_saveBmp, _T("Save this file."));
	m_pToolBar->AddTool(ID_SAVEAS, _T("Save"), m_saveAsBmp, _T("Save this file as..."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(ID_CUT, _T("Cut"), m_cutBmp, _T("Cut selected text."));
	m_pToolBar->AddTool(ID_COPY, _T("Copy"), m_copyBmp, _T("Copy selected text."));
	m_pToolBar->AddTool(ID_PASTE, _T("Paste"), m_pasteBmp, _T("Paste selected text."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(ID_UNDO, _T("Undo"), m_undoBmp, _T("Undo  action."));
	m_pToolBar->AddTool(ID_REDO, _T("Redo"), m_redoBmp, _T("Redo action."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(ID_ZOOMIN, _T("Zoom In"), m_zoomInBmp, _T("Zoom in."));
	m_pToolBar->AddTool(ID_ZOOMOUT, _T("Zoom Out"), m_zoomOutBmp, _T("Zoom out."));

	// Set and assign the toolbar
	m_pToolBar->Realize();
	this->SetToolBar(m_pToolBar);
}

void WorkoutWindow::SetupMenuBar()
{
	m_pMenuBar = new wxMenuBar();
	m_pFileMenu = new wxMenu();
	m_pEditMenu = new wxMenu();
	m_pViewMenu = new wxMenu();

	m_pFileMenu->Append(ID_SAVE, _T("&Save\tCtrl+S"));
	m_pFileMenu->Append(ID_SAVEAS, _T("&Save As...\tCtrl+Shift+S"));
	m_pFileMenu->Append(ID_OPEN, _T("&Open...\tCtrl+O"));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit"));

	m_pEditMenu->Append(ID_UNDO, _T("&Undo\tCtrl+Z"));
	m_pEditMenu->Append(ID_REDO, _T("&Redo\tCtrl+Shift+Z"));
	m_pEditMenu->AppendSeparator();
	m_pEditMenu->Append(ID_CUT, _T("&Cut\tCtrl+X"));
	m_pEditMenu->Append(ID_COPY, _T("&Copy\tCtrl+C"));
	m_pEditMenu->Append(ID_PASTE, _T("&Paste\tCtrl+V"));
	m_pEditMenu->Append(ID_SELECT_ALL, _T("&Select All\tCtrl+A"));

	m_pViewMenu->Append(ID_FULLSCREEN, _T("&Toggle Fullscreen\tF11"));
	m_pViewMenu->AppendSeparator();
	m_pViewMenu->Append(ID_ZOOMIN, _T("&Zoom In\tCtrl+Shift++"));
	m_pViewMenu->Append(ID_ZOOMOUT, _T("&Zoom Out\tCtrl+Shift+-"));

	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pEditMenu, _T("&Edit"));
	m_pMenuBar->Append(m_pViewMenu, _T("&View"));
	this->SetMenuBar(m_pMenuBar);
}

void WorkoutWindow::SetupControls()
{
	m_clearButton = new wxButton(this, ID_CLEAR_TEXT, _T("Clear Text"), wxDefaultPosition, wxDefaultSize);
	m_fontButton = new wxButton(this, ID_CHANGE_FONT, _T("Change Font"), wxDefaultPosition, wxDefaultSize);
	m_stwButton = new wxButton(this, ID_STW, _T("Save to Workouts"), wxDefaultPosition, wxDefaultSize);
	m_pTextBox = new wxTextCtrl(this, wxID_ANY, _T("Begin creating your workout:\n"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

	m_pTextBox->DragAcceptFiles(true);
	m_pTextBox->Bind(wxEVT_MOUSEWHEEL, &WorkoutWindow::OnMouse, this); // Connect the mouse event handler so zooming is not processed outside of the textbox.
}

void WorkoutWindow::SetupSizers()
{
	// Sizer setup
	m_topSizer = new wxBoxSizer(wxVERTICAL);
	m_buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(m_topSizer);
	m_topSizer->Add(m_buttonSizer);

	// Add elements
	m_buttonSizer->Add(m_clearButton, 0, wxALIGN_LEFT | wxALL, 5);
	m_buttonSizer->Add(m_fontButton, 0, wxALIGN_LEFT | wxALL, 5);
	//m_topSizer->Add(new wxStaticLine(this, wxID_STATIC), 0, wxEXPAND | wxALL, 5);
	m_topSizer->Add(m_pTextBox, 1, wxEXPAND | wxALL, 5);
	m_topSizer->Add(m_stwButton, 0, wxLEFT | wxALL, 5);
}

// Zooming

void WorkoutWindow::ZoomIn()
{
	// Add text zoom by getting the current font size and changing it accordingly, and keeping the font the user selected
	m_nFontSize = m_pTextBox->GetFont().GetPointSize();
	++m_nFontSize;
	m_pTextBox->SetFont(wxFont(m_nFontSize, m_pTextBox->GetFont().GetFamily(), m_pTextBox->GetFont().GetStyle(), m_pTextBox->GetFont().GetWeight(), false));
}

void WorkoutWindow::ZoomOut()
{
	m_nFontSize = m_pTextBox->GetFont().GetPointSize();
	--m_nFontSize;
	m_pTextBox->SetFont(wxFont(m_nFontSize, m_pTextBox->GetFont().GetFamily(), m_pTextBox->GetFont().GetStyle(), m_pTextBox->GetFont().GetWeight(), false));
}

void WorkoutWindow::AddItemToWorkoutList()
{
	m_pWorkoutList->AddItem(m_pSaveWorkoutDlg->GetWorkoutName(), m_pTextBox->GetValue());
}

void WorkoutWindow::OpenWorkout(const wxString& content)
{
	this->Show(true);
	m_pTextBox->SetValue(content);
}

// Events

void WorkoutWindow::OnSTW(wxCommandEvent& event)
{
	m_pSaveWorkoutDlg = new SaveWorkoutDialog(this, wxID_ANY, _T("Save Workout"));

	if (m_pSaveWorkoutDlg->ShowModal() == wxID_OK)
	{
		m_workoutName = m_pSaveWorkoutDlg->GetWorkoutName();
		this->AddItemToWorkoutList();
	}
}

void WorkoutWindow::OnClose(wxCloseEvent& event)
{
	this->Destroy();
}

void WorkoutWindow::OnFullScreen(wxCommandEvent& event)
{
	this->ShowFullScreen(!IsFullScreen(), wxFULLSCREEN_NOBORDER | wxFULLSCREEN_NOCAPTION);
}

void WorkoutWindow::OnDropFile(wxDropFilesEvent& event)
{
}

void WorkoutWindow::OnMouse(wxMouseEvent& event)
{
	if (event.ControlDown() && event.GetWheelRotation() > 0)
	{
		this->ZoomIn();
#ifdef _DEBUG
		//m_pTextBox->AppendText(wxString() << "Delta: " << event.GetWheelRotation() << '\n');
#endif
	}

	if (event.ControlDown() && event.GetWheelRotation() < 0)
	{
		this->ZoomOut();
#ifdef _DEBUG
		//m_pTextBox->AppendText(wxString() << "Delta: " << event.GetWheelRotation() << '\n');
#endif
	}
}

void WorkoutWindow::OnExit(wxCommandEvent& event)
{
	this->Destroy();
}

void WorkoutWindow::OnText(wxCommandEvent& event)
{
	m_bFileSaved = false;
}

void WorkoutWindow::OnClearText(wxCommandEvent& event)
{
	m_pTextBox->Clear();
}

void WorkoutWindow::OnChangeFont(wxCommandEvent& event)
{
	m_pFontDialog = new wxFontDialog(this);
	m_pFontDialog->Show(true);

	if (m_pFontDialog->ShowModal() == wxID_OK)
	{
		wxFontData fontData = m_pFontDialog->GetFontData();
		m_pTextBox->SetFont(fontData.GetChosenFont());
	}
}

void WorkoutWindow::OnOpen(wxCommandEvent& event)
{
	wxFileDialog* openDialog = new wxFileDialog(this, _T("Open text file"), wxEmptyString, wxEmptyString, _T("Text files (*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	// Check if the user has loaded a file and confirm they want to overwrite its contents.
	if (m_bActiveFile && !m_bFileSaved)
		if (wxMessageBox(_T("Current file has not been saved. Would you like to proceed?"), _T("Confirm"), wxICON_WARNING | wxYES_NO) == wxNO)
			return;

	if (openDialog->ShowModal() == wxID_OK)
	{
		// Overwrite the current text with the new text and change the window title.
		m_currentFilePath = openDialog->GetPath();
		m_currentFileName = openDialog->GetFilename();
		m_pTextBox->LoadFile(m_currentFilePath);
		this->SetLabel(wxString("Workout - ") << m_currentFileName);
		m_bActiveFile = true;
	}

	openDialog->Destroy();
}

void WorkoutWindow::OnSave(wxCommandEvent& event)
{
	m_pTextBox->SaveFile(m_saveFilePath);
	m_bFileSaved = true;
}

void WorkoutWindow::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog* saveDialog = new wxFileDialog(this, _T("Save text file"), wxEmptyString, wxEmptyString, _T("Text files (*.txt)|*.txt"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveDialog->ShowModal() == wxID_OK)
	{
		m_saveFilePath = saveDialog->GetPath();
		m_currentFileName = saveDialog->GetFilename();
		m_pTextBox->SaveFile(m_saveFilePath);
		this->SetLabel(wxString("Note Viewer - ") << m_currentFileName);
		m_bFileSaved = true;
	}

	saveDialog->Destroy();
}

void WorkoutWindow::OnCut(wxCommandEvent& event)
{
	if (m_pTextBox->CanCut())
		m_pTextBox->Cut();
}

void WorkoutWindow::OnCopy(wxCommandEvent& event)
{
	if (m_pTextBox->CanCopy())
		m_pTextBox->Copy();
}

void WorkoutWindow::OnPaste(wxCommandEvent& event)
{
	if (m_pTextBox->CanPaste())
		m_pTextBox->Paste();
}

void WorkoutWindow::OnSelectAll(wxCommandEvent& event)
{
	m_pTextBox->SelectAll();
}

void WorkoutWindow::OnUndo(wxCommandEvent& event)
{
	if (m_pTextBox->CanUndo())
		m_pTextBox->Undo();
}

void WorkoutWindow::OnRedo(wxCommandEvent& event)
{
	if (m_pTextBox->CanRedo())
		m_pTextBox->Redo();
}

void WorkoutWindow::OnZoomIn(wxCommandEvent& event)
{
	this->ZoomIn();
}

void WorkoutWindow::OnZoomOut(wxCommandEvent& event)
{
	this->ZoomOut();
}