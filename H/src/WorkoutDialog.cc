#include "WorkoutDialog.h"
#include "StandardPath.hpp"

// Event table
BEGIN_EVENT_TABLE(WorkoutDialog, wxDialog)

END_EVENT_TABLE()

WorkoutDialog::WorkoutDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
}

void WorkoutDialog::Init()
{
	this->SetupImages();
	this->SetupControls();
	this->SetupSizers();
	this->SetupWindowSizing();
}

void WorkoutDialog::SetupWindowSizing()
{
	this->SetMinSize(WD_SIZE);
	this->SetInitialSize(WD_SIZE);
}

void WorkoutDialog::SetupImages()
{
	// Bitmaps
	m_cutBmp = wxBitmap(path_data::dataDir + _T("\\Images\\cut_small.png"), wxBITMAP_TYPE_PNG);
	m_copyBmp = wxBitmap(path_data::dataDir + _T("\\Images\\copy_small.png"), wxBITMAP_TYPE_PNG);
	m_pasteBmp = wxBitmap(path_data::dataDir + _T("\\Images\\paste_small.png"), wxBITMAP_TYPE_PNG);
	m_undoBmp = wxBitmap(path_data::dataDir + _T("\\Images\\undo_small.png"), wxBITMAP_TYPE_PNG);
	m_redoBmp = wxBitmap(path_data::dataDir + _T("\\Images\\redo_small.png"), wxBITMAP_TYPE_PNG);

	// Bitmap buttons
	m_pCut = new wxBitmapButton(this, wxID_CUT, m_cutBmp);
	m_pCopy = new wxBitmapButton(this, wxID_COPY, m_copyBmp);
	m_pPaste = new wxBitmapButton(this, wxID_PASTE, m_pasteBmp);
	m_pUndo = new wxBitmapButton(this, wxID_UNDO, m_undoBmp);
	m_pRedo = new wxBitmapButton(this, wxID_REDO, m_redoBmp);
}

void WorkoutDialog::SetupControls()
{
}

void WorkoutDialog::SetupSizers()
{
	// Initialization
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pTextActionSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(m_pTopSizer);

	// Add controls and elements
}

// ========================== Events ==========================

void WorkoutDialog::OnOK(wxCommandEvent& event)
{

}

void WorkoutDialog::OnCancel(wxCommandEvent& event)
{

}