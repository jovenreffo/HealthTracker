#include <wx/valtext.h>
#include <wx/stattext.h>
#include <wx/statline.h>
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

	// Set tool tips for the buttons
	m_pCut->SetToolTip(_T("Cut selected text."));
	m_pCopy->SetToolTip(_T("Copy selected text."));
	m_pPaste->SetToolTip(_T("Paste text."));
	m_pUndo->SetToolTip(_T("Undo last action."));
	m_pRedo->SetToolTip(_T("Redo last action"));
}

void WorkoutDialog::SetupControls()
{
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxTextValidator(0, &m_workoutContent));

	m_pOk = new wxButton(this, wxID_ANY, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
}

void WorkoutDialog::SetupSizers()
{
	// Initialization
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pTextActionSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(m_pTopSizer);

	// Align the bitmap buttons
	m_pTextActionSizer->Add(m_pCut, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pTextActionSizer->Add(m_pCopy, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pTextActionSizer->Add(m_pPaste, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pTextActionSizer->Add(m_pUndo, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pTextActionSizer->Add(m_pRedo, wxSizerFlags().CentreVertical().Border(wxALL, 5));

	// Exit button sizer
	m_pButtonSizer->Add(m_pOk, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().CentreVertical().Border(wxALL, 5));

	// Add controls and elements to the top sizer
	m_pTopSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Below, begin creating your workout:")), wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
	m_pTopSizer->Add(m_pTextCtrl, wxSizerFlags().Proportion(1).Expand().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pTextActionSizer, wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().Border(wxALL, 5));
}

// ========================== Events ==========================

void WorkoutDialog::OnOK(wxCommandEvent& event)
{

}

void WorkoutDialog::OnCancel(wxCommandEvent& event)
{

}