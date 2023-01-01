#include <wx/valtext.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/filedlg.h>
#include <wx/config.h>	
#include "WorkoutWindow.h"
#include "StandardPath.hpp"

WorkoutWindow::WorkoutWindow(WorkoutList* pWorkoutList, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style, _T("WorkoutWindow")), m_pWorkoutList{pWorkoutList}
{
	this->Init();
	this->LoadConfig();
	this->SetBackgroundColour(m_pSaveWorkoutDlg->GetBackgroundColour());

	// Bind events to the controls
	m_pToolBar->Bind(wxEVT_TOOL, &WorkoutWindow::OnCut, this, wxID_CUT);
	m_pToolBar->Bind(wxEVT_TOOL, &WorkoutWindow::OnCopy, this, wxID_COPY);
	m_pToolBar->Bind(wxEVT_TOOL, &WorkoutWindow::OnPaste, this, wxID_PASTE);
	m_pToolBar->Bind(wxEVT_TOOL, &WorkoutWindow::OnUndo, this, wxID_UNDO);
	m_pToolBar->Bind(wxEVT_TOOL, &WorkoutWindow::OnRedo, this, wxID_REDO);
	m_pToolBar->Bind(wxEVT_TOOL, &WorkoutWindow::OnSave, this, wxID_SAVE);
	m_pToolBar->Bind(wxEVT_TOOL, &WorkoutWindow::OnExport, this, wxID_SAVEAS);
	m_pToolBar->Bind(wxEVT_TOOL, &WorkoutWindow::OnImport, this, wxID_OPEN);

	m_pOk->Bind(wxEVT_BUTTON, &WorkoutWindow::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &WorkoutWindow::OnCancel, this, wxID_CANCEL);
}

WorkoutWindow::~WorkoutWindow()
{
	// Unbind events from controls
	m_pToolBar->Unbind(wxEVT_TOOL, &WorkoutWindow::OnCut, this, wxID_CUT);
	m_pToolBar->Unbind(wxEVT_TOOL, &WorkoutWindow::OnCopy, this, wxID_COPY);
	m_pToolBar->Unbind(wxEVT_TOOL, &WorkoutWindow::OnPaste, this, wxID_PASTE);
	m_pToolBar->Unbind(wxEVT_TOOL, &WorkoutWindow::OnUndo, this, wxID_UNDO);
	m_pToolBar->Unbind(wxEVT_TOOL, &WorkoutWindow::OnRedo, this, wxID_REDO);
	m_pToolBar->Unbind(wxEVT_TOOL, &WorkoutWindow::OnSave, this, wxID_SAVE);
	m_pToolBar->Unbind(wxEVT_TOOL, &WorkoutWindow::OnExport, this, wxID_SAVEAS);
	m_pToolBar->Unbind(wxEVT_TOOL, &WorkoutWindow::OnImport, this, wxID_OPEN);

	m_pOk->Unbind(wxEVT_BUTTON, &WorkoutWindow::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &WorkoutWindow::OnCancel, this, wxID_CANCEL);
}

void WorkoutWindow::HandleExit()
{
	// Ensure data transfer completes successfully
	if (Validate() && TransferDataFromWindow())
	{
		this->SaveToWorkoutList();
		this->Show(false);
	}
}

__forceinline void WorkoutWindow::AddToWorkoutList()
{
	m_pWorkoutList->AddItem(m_pSaveWorkoutDlg->GetWorkoutName(), m_workoutContent);
}

void WorkoutWindow::SaveToWorkoutList()
{
	m_pSaveWorkoutDlg->Show(true);

	if (m_pSaveWorkoutDlg->ShowModal() == wxID_OK)
	{
		this->AddToWorkoutList();
	}
}

void WorkoutWindow::OpenWorkout(const wxString& content)
{
	this->Show(true);
	m_pTextCtrl->SetValue(content);
}

void WorkoutWindow::Init()
{
	m_pSaveWorkoutDlg = new SaveWorkoutDialog(this, wxID_ANY);

	this->SetupImages();
	this->SetupControls();
	this->SetupToolBar();
	this->SetupSizers();
	this->SetupWindowSizing();
}

void WorkoutWindow::LoadConfig()
{
	// Load the values of the config
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath("/Preferences");

	// Check if the spellcheck option is active from the preferences panel and enable it on the local text ctrl
	if (pConfig->Read("Spellcheck", 0L) == 1L)
		m_pTextCtrl->EnableProofCheck(wxTextProofOptions::Default());

	// Check if the user has selected a custom font
	if (pConfig->Read("CheckFont", 0L) == 1L)
	{
		m_pTextCtrl->SetFont(wxFont(
			pConfig->Read("FontSize", 10L),
			static_cast<wxFontFamily>(pConfig->Read("FontFamily", static_cast<long>(wxFONTFAMILY_DEFAULT))),
			static_cast<wxFontStyle>(pConfig->Read("FontStyle", static_cast<long>(wxFONTSTYLE_NORMAL))),
			wxFONTWEIGHT_NORMAL,
			pConfig->Read("FontUnderline", 0L),
			pConfig->Read("FaceName", "")
		));
	}
}

void WorkoutWindow::SetupToolBar()
{
#ifdef __WXMSW__ // Only add the wxTB_FLAT style if the user has windows
	m_pToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT | wxTB_FLAT);
#else
	m_pToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);
#endif

	m_pToolBar->AddTool(wxID_CUT, _T("Cut"), m_cutBmp, _T("Cut selected text."));
	m_pToolBar->AddTool(wxID_COPY, _T("Copy"), m_copyBmp, _T("Copy selected text."));
	m_pToolBar->AddTool(wxID_PASTE, _T("Paste"), m_pasteBmp, _T("Paste text from the clipboard."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(wxID_UNDO, _T("Undo"), m_undoBmp, _T("Undo last action."));
	m_pToolBar->AddTool(wxID_REDO, _T("Redo"), m_redoBmp, _T("Redo last action."));
	m_pToolBar->AddSeparator();
	m_pToolBar->AddTool(wxID_SAVE, _T("Save"), m_saveBmp, _T("Save to workouts."));
	m_pToolBar->AddTool(wxID_SAVEAS, _T("Export"), m_exportBmp, _T("Export workout as a text file."));
	m_pToolBar->AddTool(wxID_OPEN, _T("Import"), m_importBmp, _T("Import a text file."));

	m_pToolBar->Realize();
	this->SetToolBar(m_pToolBar);
}

void WorkoutWindow::SetupWindowSizing()
{
	this->SetMinSize(WD_SIZE);
	this->SetInitialSize(WD_SIZE);
	this->SetMaxSize(WD_SIZE_MAX);
}

void WorkoutWindow::SetupImages()
{
	// Bitmaps
	m_cutBmp = wxBitmap(path_data::dataDir + _T("\\Images\\cut_small.png"), wxBITMAP_TYPE_PNG);
	m_copyBmp = wxBitmap(path_data::dataDir + _T("\\Images\\copy_small.png"), wxBITMAP_TYPE_PNG);
	m_pasteBmp = wxBitmap(path_data::dataDir + _T("\\Images\\paste_small.png"), wxBITMAP_TYPE_PNG);
	m_undoBmp = wxBitmap(path_data::dataDir + _T("\\Images\\undo_small.png"), wxBITMAP_TYPE_PNG);
	m_redoBmp = wxBitmap(path_data::dataDir + _T("\\Images\\redo_small.png"), wxBITMAP_TYPE_PNG);
	m_saveBmp = wxBitmap(path_data::dataDir + _T("\\Images\\save.png"), wxBITMAP_TYPE_PNG);
	m_exportBmp = wxBitmap(path_data::dataDir + _T("\\Images\\export.png"), wxBITMAP_TYPE_PNG);
	m_importBmp = wxBitmap(path_data::dataDir + _T("\\Images\\import.png"), wxBITMAP_TYPE_PNG);
}

void WorkoutWindow::SetupControls()
{
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2, wxTextValidator(0, &m_workoutContent), _T("workouttxtctrl"));
	m_pTextCtrl->DragAcceptFiles(true);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
}

void WorkoutWindow::SetupSizers()
{
	// Initialization
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(m_pTopSizer);

	// Exit button sizer
	m_pButtonSizer->Add(m_pOk, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().CentreVertical().Border(wxALL, 5));

	// Add controls and elements to the top sizer
	m_pTopSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Below, begin creating your workout:")), wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
	m_pTopSizer->Add(m_pTextCtrl, wxSizerFlags().Proportion(1).Expand().Left().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().Border(wxALL, 5));
}

// ========================== Events ==========================

void WorkoutWindow::OnOK(wxCommandEvent& event)
{
	this->HandleExit();
}

void WorkoutWindow::OnCancel(wxCommandEvent& event)
{
	this->Destroy();
}

// text events
// perform sanity checks on the text ctrl before performing any action

void WorkoutWindow::OnCut(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanCut())
		m_pTextCtrl->Cut();
}

void WorkoutWindow::OnCopy(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanCopy())
		m_pTextCtrl->Copy();
}

void WorkoutWindow::OnPaste(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanPaste())
		m_pTextCtrl->Paste();
}

void WorkoutWindow::OnUndo(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanUndo())
		m_pTextCtrl->Undo();
}

void WorkoutWindow::OnRedo(wxCommandEvent& event)
{
	if (m_pTextCtrl->CanRedo())
		m_pTextCtrl->Redo();
}

void WorkoutWindow::OnSave(wxCommandEvent& event)
{
	this->HandleExit();
}

void WorkoutWindow::OnExport(wxCommandEvent& event)
{
	wxFileDialog* pSaveFileDialog = new wxFileDialog(this, _T("Save Workout"), wxEmptyString, wxEmptyString, _T("Text files (*.txt)|*.txt"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (pSaveFileDialog->ShowModal() == wxID_OK)
	{
		m_pTextCtrl->SaveFile(pSaveFileDialog->GetPath());
	}

	pSaveFileDialog->Destroy();
}

void WorkoutWindow::OnImport(wxCommandEvent& event)
{

}