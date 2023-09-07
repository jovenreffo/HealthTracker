#include <wx/config.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/valgen.h>
#include <wx/dc.h>
#include <wx/colordlg.h>

#include "SpreadsheetWindow.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"

// ===== AddTableDlg =====

AddTableDlg::AddTableDlg(const wxString& which, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_whichStr{ which }
{
	this->Init();
	this->BindEvents();
}

AddTableDlg::~AddTableDlg()
{
	// Unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &AddTableDlg::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &AddTableDlg::OnCancel, this, wxID_CANCEL);
}

void AddTableDlg::BindEvents()
{
	// Button events
	m_pOk->Bind(wxEVT_BUTTON, &AddTableDlg::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &AddTableDlg::OnCancel, this, wxID_CANCEL);
}

void AddTableDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void AddTableDlg::SetupControls()
{
	m_pNumCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 1, 100, 1);
	m_pNumCtrl->SetValidator(wxGenericValidator(&m_num));

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
}

void AddTableDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pCtrlSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	wxStaticText* pNum = new wxStaticText(this, wxID_STATIC, wxString("Number of ") << m_whichStr << ':', wxDefaultPosition, wxDefaultSize);
	m_pCtrlSizer->Add(pNum, wxSizerFlags().Left().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pNumCtrl, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pCtrlSizer, wxSizerFlags().CentreHorizontal());

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Left().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal());
}

void AddTableDlg::SetupSizing()
{
	wxSize size = this->GetBestSize();
	wxSize initial = wxSize(size.x + 50, size.y + 35);
	wxSize max = wxSize(size.x + 125, size.y + 75);

	this->SetMinSize(size);
	this->SetInitialSize(initial);
	this->SetMaxSize(max);
}

void AddTableDlg::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void AddTableDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

// DeleteElementsDlg

DeleteElementsDlg::DeleteElementsDlg(wxGrid* pGrid, const wxString& which, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_pGrid{ pGrid }, m_whichStr{which}
{
	this->Init();

	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &DeleteElementsDlg::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &DeleteElementsDlg::OnCancel, this, wxID_CANCEL);
}

DeleteElementsDlg::~DeleteElementsDlg()
{
	// Unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &DeleteElementsDlg::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &DeleteElementsDlg::OnCancel, this, wxID_CANCEL);
}

void DeleteElementsDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void DeleteElementsDlg::SetupControls()
{
	m_pNumCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 1, 100, 1);
	m_pNumCtrl->SetToolTip(wxString(_T("Number of ")) << m_whichStr << _T(" to delete."));
	m_pNumCtrl->SetValidator(wxGenericValidator(&m_num));

	m_pCheckBox = new wxCheckBox(this, wxID_ANY, _T("Remove from front"));

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
}

void DeleteElementsDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pCtrlSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	wxStaticText* pNum = new wxStaticText(this, wxID_STATIC, wxString("Number of ") << m_whichStr << ':', wxDefaultPosition, wxDefaultSize);
	m_pCtrlSizer->Add(pNum, wxSizerFlags().Left().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pNumCtrl, wxSizerFlags().Left().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pCheckBox, wxSizerFlags().Left().Border(wxALL, 5));
	m_pCtrlSizer->AddSpacer(5);
	m_pTopSizer->Add(m_pCtrlSizer, wxSizerFlags().CentreHorizontal());

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Left().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal());
}

void DeleteElementsDlg::SetupSizing()
{
	wxSize size = this->GetBestSize();
	wxSize initial = wxSize(size.x + 50, size.y + 35);
	wxSize max = wxSize(size.x + 125, size.y + 75);

	this->SetMinSize(size);
	this->SetInitialSize(initial);
	this->SetMaxSize(max);
}

void DeleteElementsDlg::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		if (m_pCheckBox->IsChecked())
			m_bRemoveFromFront = true;

		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void DeleteElementsDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

// ChangeCellBackgroundDlg

ChangeCellBackgroundDlg::ChangeCellBackgroundDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
	
	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &ChangeCellBackgroundDlg::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &ChangeCellBackgroundDlg::OnCancel, this, wxID_CANCEL);
}

ChangeCellBackgroundDlg::~ChangeCellBackgroundDlg()
{
	// Unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &ChangeCellBackgroundDlg::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &ChangeCellBackgroundDlg::OnCancel, this, wxID_CANCEL);
}

void ChangeCellBackgroundDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void ChangeCellBackgroundDlg::SetupControls()
{
	m_pRowSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000, 0);
	m_pRowSpin->SetValidator(wxGenericValidator(&m_row));

	m_pColSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000, 0);
	m_pColSpin->SetValidator(wxGenericValidator(&m_col));

	m_pClrPicker = new wxColourPickerCtrl(this, wxID_ANY);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"));
}

void ChangeCellBackgroundDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pCtrlSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pCtrlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Row: ")), wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pRowSpin, wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Column: ")), wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pColSpin, wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Colour: ")), wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pClrPicker, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(m_pCtrlSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
}

void ChangeCellBackgroundDlg::SetupSizing()
{
	wxSize size{ this->GetBestSize() };
	this->SetMinSize(size);
	this->SetInitialSize(wxSize(size.GetX() + 50, size.GetY() + 35));
}

void ChangeCellBackgroundDlg::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		m_colour = m_pClrPicker->GetColour();

		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void ChangeCellBackgroundDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

// ==== ChangeCellFontDlg ====

ChangeCellFontDlg::ChangeCellFontDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();

	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &ChangeCellFontDlg::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &ChangeCellFontDlg::OnCancel, this, wxID_CANCEL);
	m_pFontPicker->Bind(wxEVT_FONTPICKER_CHANGED, &ChangeCellFontDlg::OnSelectFont, this);
}

ChangeCellFontDlg::~ChangeCellFontDlg()
{
	// Unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &ChangeCellFontDlg::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &ChangeCellFontDlg::OnCancel, this, wxID_CANCEL);
	m_pFontPicker->Unbind(wxEVT_FONTPICKER_CHANGED, &ChangeCellFontDlg::OnSelectFont, this);
}

void ChangeCellFontDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void ChangeCellFontDlg::SetupControls()
{
	m_pRowSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 100, 0);
	m_pRowSpin->SetValidator(wxGenericValidator(&m_row));

	m_pColSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 100, 0);
	m_pColSpin->SetValidator(wxGenericValidator(&m_col));

	m_pFontPicker = new wxFontPickerCtrl(this, wxID_ANY);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"));
}

void ChangeCellFontDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pCtrlSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pCtrlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Row: ")), wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pRowSpin, wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Column: ")), wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pColSpin, wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Font: ")), wxSizerFlags().Border(wxALL, 5));
	m_pCtrlSizer->Add(m_pFontPicker, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(m_pCtrlSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
}

void ChangeCellFontDlg::SetupSizing()
{
	wxSize size{ this->GetBestSize() };
	this->SetMinSize(size);
	this->SetInitialSize(wxSize(size.GetX() + 50, size.GetY() + 35));
}

void ChangeCellFontDlg::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		m_font = m_pFontPicker->GetFont();

		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void ChangeCellFontDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

void ChangeCellFontDlg::OnSelectFont(wxFontPickerEvent& event)
{
	m_font = m_pFontPicker->GetSelectedFont();
	this->Refresh();
}

// ===== ChangeCellSizeDlg =====

ChangeCellSizeDlg::ChangeCellSizeDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();

	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &ChangeCellSizeDlg::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &ChangeCellSizeDlg::OnCancel, this, wxID_CANCEL);
}

ChangeCellSizeDlg::~ChangeCellSizeDlg()
{
	// Unbind events
	m_pOk->Unbind(wxEVT_BUTTON, &ChangeCellSizeDlg::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &ChangeCellSizeDlg::OnCancel, this, wxID_CANCEL);
}

void ChangeCellSizeDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
	this->ToolTips();
}

void ChangeCellSizeDlg::SetupControls()
{
	// Spin controls
	m_pRow = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000, 0);
	m_pCol = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000, 0);
	m_pNumRows = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000, 0);
	m_pNumCols = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 0, 10000, 0);
	// Validators
	m_pRow->SetValidator(wxGenericValidator(&m_row));
	m_pCol->SetValidator(wxGenericValidator(&m_col));
	m_pNumRows->SetValidator(wxGenericValidator(&m_numRows));
	m_pNumCols->SetValidator(wxGenericValidator(&m_numCols));

	// Buttons
	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"));
}

void ChangeCellSizeDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pControlSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Row:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pRow, wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Column:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pCol, wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Number of Rows:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pNumRows, wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Number of Columns:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pNumCols, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(m_pControlSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
}

void ChangeCellSizeDlg::SetupSizing()
{
	wxSize size{ this->GetBestSize() };
	this->SetMinSize(size);
	this->SetInitialSize(wxSize(size.GetX() + 50, size.GetY() + 35));
}

void ChangeCellSizeDlg::ToolTips()
{
	m_pNumRows->SetToolTip(_T("Number of rows the new cell will occupy."));
	m_pNumCols->SetToolTip(_T("Number of columns the new cell will occupy."));
}

void ChangeCellSizeDlg::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		// Secondary validation
		m_row = m_pRow->GetValue();
		m_col = m_pCol->GetValue();
		m_numRows = m_pNumRows->GetValue();
		m_numCols = m_pNumCols->GetValue();

		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void ChangeCellSizeDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

// ===== AddWorkoutDayDlg =====

AddWorkoutDayDlg::AddWorkoutDayDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();

	// Bind events
	m_pNumCtrl->Bind(wxEVT_TEXT_ENTER, &AddWorkoutDayDlg::OnEnter, this);
	m_pNumCtrl->Bind(wxEVT_TEXT, &AddWorkoutDayDlg::OnExceedLimit, this);
	m_pOk->Bind(wxEVT_BUTTON, &AddWorkoutDayDlg::OnOK, this, wxID_OK);
	m_pCancel->Bind(wxEVT_BUTTON, &AddWorkoutDayDlg::OnCancel, this, wxID_CANCEL);
}

AddWorkoutDayDlg::~AddWorkoutDayDlg()
{
	// Unbind events
	m_pNumCtrl->Unbind(wxEVT_TEXT_ENTER, &AddWorkoutDayDlg::OnEnter, this);
	m_pNumCtrl->Unbind(wxEVT_TEXT, &AddWorkoutDayDlg::OnExceedLimit, this);
	m_pOk->Unbind(wxEVT_BUTTON, &AddWorkoutDayDlg::OnOK, this, wxID_OK);
	m_pCancel->Unbind(wxEVT_BUTTON, &AddWorkoutDayDlg::OnCancel, this, wxID_CANCEL);
}

void AddWorkoutDayDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
	this->ToolTip();
}

void AddWorkoutDayDlg::SetupControls()
{
	m_pNumCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 1, 100, 1);
	m_pNumCtrl->SetValidator(wxGenericValidator(&m_numDays));

	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"));
}

void AddWorkoutDayDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pControlSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	this->SetSizerAndFit(m_pTopSizer);

	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Number of days:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pNumCtrl, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(m_pControlSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
}

void AddWorkoutDayDlg::SetupSizing()
{
	wxSize size{ this->GetBestSize() };
	this->SetMinSize(size);
	this->SetInitialSize(wxSize(size.GetX() + 50, size.GetY() + 35));
}

void AddWorkoutDayDlg::ToolTip()
{
	m_pNumCtrl->SetToolTip(_T("Number of days to be added. Maximum 100 at a time."));
}

void AddWorkoutDayDlg::OnOK(wxCommandEvent& event)
{
	if (m_pNumCtrl->GetValue() > 100)
	{
		wxMessageBox(_T("A maximum of 100 days can be added at a time."), _T("Limit Exceeded"), wxICON_EXCLAMATION | wxOK);
		return;
	}

	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void AddWorkoutDayDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

void AddWorkoutDayDlg::OnEnter(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void AddWorkoutDayDlg::OnExceedLimit(wxCommandEvent& event)
{
	if (m_pNumCtrl->GetValue() > 100)
	{
		wxMessageBox(_T("A maximum of 100 days can be added at a time."), _T("Limit Exceeded"), wxICON_EXCLAMATION | wxOK);
	}
}

// ===== SSWToolBar =====

SSWToolBar::SSWToolBar(ExerciseGrid* pExerciseGrid, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxToolBar(parent, id, pos, size, style), m_pExerciseGrid{ pExerciseGrid }
{
	this->Init();
	this->BindEvents();
}

SSWToolBar::~SSWToolBar()
{
	this->UnbindEvents();
}

void SSWToolBar::Init()
{
	this->SetupBitmaps();
	this->SetupTools();
}

void SSWToolBar::SetupBitmaps()
{
	// SSWTB = Spread sheet window tool bar
	m_undoBmp = wxBitmap(path_data::dataDir + _T("\\Images\\SSWTB\\undo20.png"), wxBITMAP_TYPE_PNG);
	m_redoBmp = wxBitmap(path_data::dataDir + _T("\\Images\\SSWTB\\redo20.png"), wxBITMAP_TYPE_PNG);

	m_cutBmp = wxBitmap(path_data::dataDir + _T("\\Images\\SSWTB\\cut20.png"), wxBITMAP_TYPE_PNG);
	m_copyBmp = wxBitmap(path_data::dataDir + _T("\\Images\\SSWTB\\copy20.png"), wxBITMAP_TYPE_PNG);
	m_pasteBmp = wxBitmap(path_data::dataDir + _T("\\Images\\SSWTB\\paste20.png"), wxBITMAP_TYPE_PNG);

	m_fontBmp = wxBitmap(path_data::dataDir + _T("\\Images\\SSWTB\\change_font.png"), wxBITMAP_TYPE_PNG);
	m_fillBmp = wxBitmap(path_data::dataDir + _T("\\Images\\SSWTB\\fill20.png"), wxBITMAP_TYPE_PNG);
}

void SSWToolBar::SetupTools()
{
	this->AddTool(wxID_UNDO, _T("Undo"), m_undoBmp, _T("Undo last action."));
	this->AddTool(wxID_REDO, _T("Redo"), m_redoBmp, _T("Redo last action."));
	this->AddSeparator();
	this->AddTool(wxID_CUT, _T("Cut"), m_cutBmp, _T("Cut selected item."));
	this->AddTool(wxID_COPY, _T("Copy"), m_copyBmp, _T("Copy selected item."));
	this->AddTool(wxID_PASTE, _T("Paste"), m_pasteBmp, _T("Paste selected item."));
	this->AddSeparator();
	this->AddTool((int)SSWTB::ID_CHANGE_FONT, _T("Change Font"), m_fontBmp, _T("Set cell font."));
	this->AddTool((int)SSWTB::ID_SET_FILL, _T("Set Fill"), m_fillBmp, _T("Set cell fill colour."));
}

void SSWToolBar::BindEvents()
{
	// Toolbar events
	this->Bind(wxEVT_TOOL, &SSWToolBar::OnChangeFont, this, (int)SSWTB::ID_CHANGE_FONT);
	this->Bind(wxEVT_TOOL, &SSWToolBar::OnSetFill, this, (int)SSWTB::ID_SET_FILL);
	this->Bind(wxEVT_TOOL, &SSWToolBar::OnCopy, this, wxID_COPY);
	this->Bind(wxEVT_TOOL, &SSWToolBar::OnPaste, this, wxID_PASTE);
	this->Bind(wxEVT_TOOL, &SSWToolBar::OnCut, this, wxID_CUT);
}

void SSWToolBar::UnbindEvents()
{
	// tb events
	this->Unbind(wxEVT_TOOL, &SSWToolBar::OnChangeFont, this, (int)SSWTB::ID_CHANGE_FONT);
	this->Unbind(wxEVT_TOOL, &SSWToolBar::OnSetFill, this, (int)SSWTB::ID_SET_FILL);
	this->Unbind(wxEVT_TOOL, &SSWToolBar::OnCopy, this, wxID_COPY);
	this->Unbind(wxEVT_TOOL, &SSWToolBar::OnPaste, this, wxID_PASTE);
	this->Unbind(wxEVT_TOOL, &SSWToolBar::OnCut, this, wxID_CUT);
}

void SSWToolBar::OnUndo(wxCommandEvent& event)
{
}

void SSWToolBar::OnRedo(wxCommandEvent& event)
{
}

void SSWToolBar::OnCut(wxCommandEvent& event)
{
	// copy the contents of the cell before erasing it
	m_currCellState = m_pExerciseGrid->GetSelectedCellState();

	wxGridCellCoords selected = m_pExerciseGrid->GetSelectedCell();
	int r = selected.GetRow();
	int c = selected.GetCol();

	// Load the config, we will need it to get the default font
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	m_pExerciseGrid->SetCellSize(r, c, 1, 1); // reset cell size to 1rowx1col
	m_pExerciseGrid->SetCellValue(r, c,wxEmptyString); // set the cell to an empty string
	m_pExerciseGrid->SetCellFont(r, c, wxFont( // reset the font to the one that is selected in the preferences dialog
		pConfig->Read("FontSize", 10L),
		static_cast<wxFontFamily>(pConfig->Read("FontFamily", static_cast<long>(wxFONTFAMILY_DEFAULT))),
		static_cast<wxFontStyle>(pConfig->Read("FontStyle", static_cast<long>(wxFONTSTYLE_NORMAL))),
		wxFONTWEIGHT_NORMAL,
		pConfig->Read("FontUnderline", 0L),
		pConfig->Read("FaceName", "")
	));
}

void SSWToolBar::OnCopy(wxCommandEvent& event)
{
	m_currCellState = m_pExerciseGrid->GetSelectedCellState();
}

void SSWToolBar::OnPaste(wxCommandEvent& event)
{
	wxGridCellCoords selected = m_pExerciseGrid->GetSelectedCell();
	int r = selected.GetRow();
	int c = selected.GetCol();

	int sizeX = m_currCellState.GetCellSize().GetX();
	int sizeY = m_currCellState.GetCellSize().GetY();

	if ((selected.GetRow() >= 0) && (selected.GetCol() >= 0))
	{
		m_pExerciseGrid->SetCellValue(selected, m_currCellState.GetCellValue());
		m_pExerciseGrid->SetCellFont(r, c, m_currCellState.GetCellFont());
		m_pExerciseGrid->SetCellSize(r, c, sizeX, sizeY);
		m_pExerciseGrid->SetCellBackgroundColour(r, c, m_currCellState.GetCellColour());
	}
}

void SSWToolBar::OnChangeFont(wxCommandEvent& event)
{
	// Create a font dialog to have the user select a font
	wxFontDialog* pFontDlg = new wxFontDialog(this);
	pFontDlg->Show(true);

	wxGridCellCoords selected = m_pExerciseGrid->GetSelectedCell();

	if (pFontDlg->ShowModal() == wxID_OK)
	{
		wxFont font = pFontDlg->GetFontData().GetChosenFont();
		m_pExerciseGrid->SetCellFont(selected.GetRow(), selected.GetCol(), font);
	}
}

void SSWToolBar::OnSetFill(wxCommandEvent& event)
{
	// Create a colour dialog to have the user select a colour
	wxColourDialog* pColourDlg = new wxColourDialog(this);
	pColourDlg->Show(true);

	wxGridCellCoords selected = m_pExerciseGrid->GetSelectedCell();

	if (pColourDlg->ShowModal() == wxID_OK)
	{
		wxColour clr = pColourDlg->GetColourData().GetColour();
		m_pExerciseGrid->SetCellBackgroundColour(selected.GetRow(), selected.GetCol(), clr);
	}
}

// ===== SpreadsheetWindow =====

SpreadsheetWindow::SpreadsheetWindow(wxWindow* parent,
	wxWindowID id,
	const wxString& title,
	const wxPoint& pos,
	const wxSize& size,
	long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	this->Init();
	this->BindEvents();
	this->CentreOnScreen();

}

SpreadsheetWindow::~SpreadsheetWindow()
{
	// Unbind events
	m_pFileMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnExit, this, wxID_EXIT);
	m_pInsertMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnAddCol, this, (int)SSW::ID_INSERT_COL);
	m_pInsertMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnAddRow, this, (int)SSW::ID_INSERT_ROW);
	m_pInsertMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnInsertDay, this, (int)SSW::ID_INSERT_DAY);
	m_pResetSubMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnResetTablePosition, this, (int)SSW::ID_RESET_TABLE_POS);
	m_pResetSubMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnResetTableSize, this, (int)SSW::ID_RESET_TABLE_SIZE);
	m_pResetSubMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnResetTableLayout, this, (int)SSW::ID_RESET_TABLE_LAYOUT);
	m_pModifySubMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnChangeBackgroundColour, this, (int)SSW::ID_CHANGE_CELL_BG_COLOUR);
	m_pModifySubMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnChangeCellFont, this, (int)SSW::ID_CHANGE_CELL_FONT);
	m_pModifySubMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnChangeCellSize, this, (int)SSW::ID_CHANGE_CELL_SIZE);

	m_pEditMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnClearTableConfiguration, this, (int)SSW::ID_CLEAR_TABLE_CONFIG);
	m_pEditDeleteMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnDeleteRows, this, (int)SSW::ID_DELETE_ROW);
	m_pEditDeleteMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnDeleteCols, this, (int)SSW::ID_DELETE_COL);

	// Save the config
	this->SaveConfig();
}

void SpreadsheetWindow::LoadConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/SSW/"));
	
	// Read the number of rows & cols from the config
	m_numRows = pConfig->Read(_T("NumRows"), 0L);
	m_numCols = pConfig->Read(_T("NumCols"), 0L);
#ifdef _DEBUG
	//wxLogMessage(_T("Num Rows: %d\nNum Cols: %d"), m_numRows, m_numCols);
#endif
}

void SpreadsheetWindow::SaveConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/SSW/"));

	// Write the number of rows & columns to the config
	m_numRows = m_pGrid->GetNumberRows();
	m_numCols = m_pGrid->GetNumberCols();

	pConfig->Write(_T("NumRows"), m_numRows);
	pConfig->Write(_T("NumCols"), m_numCols);
}

bool SpreadsheetWindow::Create(wxWindow* parent,
	wxWindowID id,
	const wxString& title,
	const wxPoint& pos,
	const wxSize& size,
	long style)
{
	wxFrame::Create(parent, id, title, pos, size, style);
	this->Init();
	this->BindEvents();
	this->CentreOnScreen();
	this->LoadConfig();

	return true;
}

void SpreadsheetWindow::BindEvents()
{
	// Menu events
	m_pFileMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnExit, this, wxID_EXIT);
	m_pInsertMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnAddCol, this, (int)SSW::ID_INSERT_COL);
	m_pInsertMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnAddRow, this, (int)SSW::ID_INSERT_ROW);
	m_pInsertMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnInsertDay, this, (int)SSW::ID_INSERT_DAY);
	m_pResetSubMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnResetTablePosition, this, (int)SSW::ID_RESET_TABLE_POS);
	m_pResetSubMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnResetTableSize, this, (int)SSW::ID_RESET_TABLE_SIZE);
	m_pResetSubMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnResetTableLayout, this, (int)SSW::ID_RESET_TABLE_LAYOUT);
	m_pModifySubMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnChangeBackgroundColour, this, (int)SSW::ID_CHANGE_CELL_BG_COLOUR);
	m_pModifySubMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnChangeCellFont, this, (int)SSW::ID_CHANGE_CELL_FONT);
	m_pModifySubMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnChangeCellSize, this, (int)SSW::ID_CHANGE_CELL_SIZE);

	m_pEditMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnClearTableConfiguration, this, (int)SSW::ID_CLEAR_TABLE_CONFIG);
	m_pEditDeleteMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnDeleteRows, this, (int)SSW::ID_DELETE_ROW);
	m_pEditDeleteMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnDeleteCols, this, (int)SSW::ID_DELETE_COL);
}

void SpreadsheetWindow::Init()
{
	// Load config
	this->LoadConfig();

	// Setup
	this->SetupControls();
	this->SetupSizers();
	this->SetupMenu();
	this->SetupToolBar();
	this->SetupSizing();
}

void SpreadsheetWindow::SetupMenu()
{
	m_pFileMenu = new wxMenu();
	m_pExportSubMenu = new wxMenu();
	m_pInsertMenu = new wxMenu();
	m_pEditMenu = new wxMenu();
	m_pResetSubMenu = new wxMenu();
	m_pModifySubMenu = new wxMenu();
	m_pEditDeleteMenu = new wxMenu();
	m_pMenuBar = new wxMenuBar();

	// File menu + export menu
	m_pExportSubMenu->Append((int)SSW::ID_EXPORT_PDF, _T("&PDF"));

	m_pFileMenu->Append(wxID_SAVEAS, _T("&Save As"));
	m_pFileMenu->AppendSubMenu(m_pExportSubMenu, _T("&Export"));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit"));

	// Insert menu
	m_pInsertMenu->Append((int)SSW::ID_INSERT_COL, _T("&New Column"));
	m_pInsertMenu->Append((int)SSW::ID_INSERT_ROW, _T("&New Row"));
	m_pInsertMenu->Append((int)SSW::ID_INSERT_DAY, _T("&New Workout Day"));

	// Edit menu
	m_pResetSubMenu->Append((int)SSW::ID_RESET_TABLE_SIZE, _T("&Cell Size"));
	m_pResetSubMenu->Append((int)SSW::ID_RESET_TABLE_POS, _T("&Table Position"));
	m_pResetSubMenu->Append((int)SSW::ID_RESET_TABLE_LAYOUT, _T("&Table Configuration"));

	m_pModifySubMenu->Append((int)SSW::ID_CHANGE_CELL_BG_COLOUR, _T("&Background Colour"));
	m_pModifySubMenu->Append((int)SSW::ID_CHANGE_CELL_FONT, _T("&Font"));
	m_pModifySubMenu->Append((int)SSW::ID_CHANGE_CELL_SIZE, _T("&Size"));

	m_pEditDeleteMenu->Append((int)SSW::ID_DELETE_ROW, _T("Row"));
	m_pEditDeleteMenu->Append((int)SSW::ID_DELETE_COL, _T("Column"));


	m_pEditMenu->Append((int)SSW::ID_CLEAR_TABLE_CONFIG, _T("&Clear Configuration"));
	m_pEditMenu->Append((int)SSW::ID_RESET_GRID_DIMENSIONS, _T("&Grid Dimensions"));
	m_pEditMenu->AppendSubMenu(m_pEditDeleteMenu, _T("&Delete..."));
	m_pEditMenu->AppendSubMenu(m_pResetSubMenu, _T("&Reset..."));
	m_pEditMenu->AppendSubMenu(m_pModifySubMenu, _T("&Change Cell..."));

	// Menubar
	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pInsertMenu, _T("&Insert"));
	m_pMenuBar->Append(m_pEditMenu, _T("&Edit"));
	this->SetMenuBar(m_pMenuBar);
}

void SpreadsheetWindow::SetupToolBar()
{
	m_pToolBar = new SSWToolBar(m_pGrid, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT);
	m_pToolBar->Realize();
	this->SetToolBar(m_pToolBar);
}

void SpreadsheetWindow::SetupSizing()
{
	this->SetInitialSize(SSW_SIZE);
}

void SpreadsheetWindow::SetupControls()
{
	m_pGrid = new ExerciseGrid(m_numRows, m_numCols, this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
}

void SpreadsheetWindow::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopSizer->Add(m_pGrid, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

// Events

void SpreadsheetWindow::OnExit(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to exit?"), _T("Confirm"), wxYES_NO | wxICON_WARNING) == wxYES)
		this->Close(true);
}

void SpreadsheetWindow::OnSave(wxCommandEvent& event)
{
}

void SpreadsheetWindow::OnExportPDF(wxCommandEvent& event)
{
}

void SpreadsheetWindow::OnAddRow(wxCommandEvent& event)
{
	m_pAddTableDlg = new AddTableDlg(_T("Rows"), this, wxID_ANY, _T("Add New Row(s)"));
	m_pAddTableDlg->Show(true);

	if (m_pAddTableDlg->ShowModal() == wxID_OK)
	{
		m_pGrid->AppendRows(m_pAddTableDlg->GetNum(), true);
	}
}

void SpreadsheetWindow::OnAddCol(wxCommandEvent& event)
{
	m_pAddTableDlg = new AddTableDlg(_T("Columns"), this, wxID_ANY, _T("Add New Column(s)"));
	m_pAddTableDlg->Show(true);

	if (m_pAddTableDlg->ShowModal() == wxID_OK)
	{
		m_pGrid->AppendCols(m_pAddTableDlg->GetNum(), true);
	}
}

void SpreadsheetWindow::OnInsertDay(wxCommandEvent& event)
{
	m_pAddWorkoutDayDlg = new AddWorkoutDayDlg(this, wxID_ANY);
	m_pAddWorkoutDayDlg->Show(true);

	if (m_pAddWorkoutDayDlg->ShowModal() == wxID_OK)
	{
		int numDays{ m_pAddWorkoutDayDlg->GetNumDays() };

		for (auto i{ 0 }; i < numDays; ++i)
			m_pGrid->AddWorkoutDay();
	}
}

void SpreadsheetWindow::OnResetTablePosition(wxCommandEvent& event)
{
	m_pGrid->ResetTablePosition();
}

void SpreadsheetWindow::OnResetTableSize(wxCommandEvent& event)
{
	m_pGrid->ResetTableSize();
}

void SpreadsheetWindow::OnResetTableLayout(wxCommandEvent& event)
{
	m_pGrid->ResetTableSize();
	m_pGrid->ResetTablePosition();

	for (auto r{ 0 }; r < m_pGrid->GetNumberRows(); ++r)
	{
		for (auto c{ 0 }; c < m_pGrid->GetNumberCols(); ++c)
		{
			m_pGrid->SetCellValue(wxGridCellCoords(r, c), wxEmptyString);
			m_pGrid->SetCellBackgroundColour(r, c, wxColour(255, 255, 255));
		}
	}
	m_pGrid->SetupWorkoutTemplate();
}

void SpreadsheetWindow::OnClearTableConfiguration(wxCommandEvent& event)
{
	m_pGrid->ResetTablePosition();
	m_pGrid->ResetTableSize();

	for (auto r{ 0 }; r < m_pGrid->GetNumberRows(); ++r)
	{
		for (auto c{ 0 }; c < m_pGrid->GetNumberCols(); ++c)
		{
			m_pGrid->SetCellValue(wxGridCellCoords(r, c), wxEmptyString);
			m_pGrid->SetCellBackgroundColour(r, c, wxColour(255, 255, 255));
		}
	}

	// Reset the cell where the title is to its default size
	m_pGrid->SetCellSize(0, 0, 1, 1);
}

void SpreadsheetWindow::OnChangeBackgroundColour(wxCommandEvent& event)
{
	m_pCCBD = new CCBD(this, wxID_ANY, _T("Change Cell Background Colour"));
	m_pCCBD->Show(true);

	if (m_pCCBD->ShowModal() == wxID_OK)
	{
		m_pGrid->SetCellBackgroundColour(m_pCCBD->GetRow(), m_pCCBD->GetCol(), m_pCCBD->GetColour());
	}
}

void SpreadsheetWindow::OnChangeCellFont(wxCommandEvent& event)
{
	m_pCCFD = new ChangeCellFontDlg(this, wxID_ANY, _T("Change Cell Font"));
	m_pCCFD->Show(true);

	if (m_pCCFD->ShowModal() == wxID_OK)
	{
		wxFont font = m_pCCFD->GetPickerCtrl()->GetSelectedFont();

		m_pGrid->SetCellFont(m_pCCFD->GetRow(), m_pCCFD->GetCol(), font);
		this->Refresh();
	}
}

void SpreadsheetWindow::OnChangeCellSize(wxCommandEvent& event)
{
	m_pCCSD = new ChangeCellSizeDlg(this, wxID_ANY);
	m_pCCSD->Show(true);

	if (m_pCCSD->ShowModal() == wxID_OK)
	{
		m_pGrid->SetCellSize(m_pCCSD->GetRow(), m_pCCSD->GetCol(), m_pCCSD->GetNumRows(), m_pCCSD->GetNumCols());
	}
}

void SpreadsheetWindow::OnDeleteRows(wxCommandEvent& event)
{
	m_pDeleteElemsDlg = new DeleteElementsDlg(m_pGrid, _T("Rows"), this, wxID_ANY, _T("Delete Row(s)"));
	m_pDeleteElemsDlg->Show(true);

	if (m_pDeleteElemsDlg->ShowModal() == wxID_OK)
	{
		if (m_pDeleteElemsDlg->IsFrontChecked())
		{
			// Delete rows from the front
			m_pGrid->DeleteRows(0, m_pDeleteElemsDlg->GetNum());
		}
		else
		{
			int pos{ m_pGrid->GetNumberRows() - m_pDeleteElemsDlg->GetNum() };
			m_pGrid->DeleteRows(pos, m_pDeleteElemsDlg->GetNum());
		}
	}
}

void SpreadsheetWindow::OnDeleteCols(wxCommandEvent& event)
{
	m_pDeleteElemsDlg = new DeleteElementsDlg(m_pGrid, _T("Columns"), this, wxID_ANY, _T("Delete Column(s)"));
	m_pDeleteElemsDlg->Show(true);

	if (m_pDeleteElemsDlg->ShowModal() == wxID_OK)
	{
		if (m_pDeleteElemsDlg->IsFrontChecked())
		{
			// delete columns from the front
			m_pGrid->DeleteCols(0, m_pDeleteElemsDlg->GetNum());
		}
		else
		{
			int pos{ m_pGrid->GetNumberCols() - m_pDeleteElemsDlg->GetNum() };
			m_pGrid->DeleteCols(pos, m_pDeleteElemsDlg->GetNum());
		}
	}
}

// ===== ExerciseGrid ======

ExerciseGrid::ExerciseGrid(int rows, int cols, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxGrid(parent, id, pos, size, style), m_numRows{ rows }, m_numCols{ cols }
{
	// Grid setup
	if (!m_numRows || !m_numCols)
		this->CreateGrid(100, 10);
	else
		this->CreateGrid(m_numRows, m_numCols);
	this->EnableDragCell(true);
	this->EnableDragColMove(true);
	this->EnableDragRowMove(true);

	// Grid member initialization
	this->Init();
	this->SetupLabelArray();

	// Workout template setup
	this->SetupWorkoutTemplate();

	// Bind events
	this->Bind(wxEVT_GRID_CELL_CHANGED, &ExerciseGrid::OnUpdateCell, this);
	this->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &ExerciseGrid::OnLeftClickCell, this);
	this->Bind(wxEVT_GRID_SELECT_CELL, &ExerciseGrid::OnSelectCell, this);
	this->Bind(wxEVT_GRID_CELL_RIGHT_CLICK, &ExerciseGrid::OnRightClickCell, this);
	m_pEditCellSub->Bind(wxEVT_MENU, &ExerciseGrid::OnChangeBackgroundColour, this, (int)SSW::ID_CHANGE_CELL_BG_COLOUR);
	m_pEditCellSub->Bind(wxEVT_MENU, &ExerciseGrid::OnChangeCellFont, this, (int)SSW::ID_CHANGE_CELL_FONT);
	m_pEditCellSub->Bind(wxEVT_MENU, &ExerciseGrid::OnChangeCellSize, this, (int)SSW::ID_CHANGE_CELL_SIZE);
}

ExerciseGrid::~ExerciseGrid()
{
	// Unbind events
	this->Unbind(wxEVT_GRID_CELL_CHANGED, &ExerciseGrid::OnUpdateCell, this);
	this->Unbind(wxEVT_GRID_CELL_LEFT_CLICK, &ExerciseGrid::OnLeftClickCell, this);
	this->Unbind(wxEVT_GRID_SELECT_CELL, &ExerciseGrid::OnSelectCell, this);
	this->Unbind(wxEVT_GRID_CELL_RIGHT_CLICK, &ExerciseGrid::OnRightClickCell, this);
	m_pEditCellSub->Unbind(wxEVT_MENU, &ExerciseGrid::OnChangeBackgroundColour, this, (int)SSW::ID_CHANGE_CELL_BG_COLOUR);
	m_pEditCellSub->Unbind(wxEVT_MENU, &ExerciseGrid::OnChangeCellFont, this, (int)SSW::ID_CHANGE_CELL_FONT);
	m_pEditCellSub->Unbind(wxEVT_MENU, &ExerciseGrid::OnChangeCellSize, this, (int)SSW::ID_CHANGE_CELL_SIZE);
}

void ExerciseGrid::ResetTablePosition()
{
	this->ResetColPos();
	this->ResetRowPos();
}

void ExerciseGrid::ResetTableSize()
{
	int defCol{ this->GetDefaultColSize() };
	int defRow{ this->GetDefaultRowSize() };
	
	// loop through rows and cols to reset their sizes
	for (auto i{ 0 }; i < GetNumberRows(); ++i)
	{
		this->SetRowSize(i, defRow);
	}
	for (auto i{ 0 }; i < GetNumberCols(); ++i)
	{
		this->SetColSize(i, defCol);
	}
}

void ExerciseGrid::Init()
{
	this->SetupConfig();
	this->SetupMenu();
}

void ExerciseGrid::SetupConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/Preferences/"));

	if (pConfig->Read(_T("CheckFont"), 0L) == 1L)
	{
		m_cellFont = wxFont(
			pConfig->Read("FontSize", 10L),
			static_cast<wxFontFamily>(pConfig->Read("FontFamily", static_cast<long>(wxFONTFAMILY_DEFAULT))),
			static_cast<wxFontStyle>(pConfig->Read("FontStyle", static_cast<long>(wxFONTSTYLE_NORMAL))),
			wxFONTWEIGHT_NORMAL,
			pConfig->Read("FontUnderline", 0L),
			pConfig->Read("FaceName", ""));

		for (auto rows{ 0 }; rows < this->GetNumberRows(); ++rows)
		{
			for (auto cols{ 0 }; cols < this->GetNumberCols(); ++cols)
			{
				this->SetCellFont(rows, cols, m_cellFont);
			}
		}
	}
}

void ExerciseGrid::SetupMenu()
{
	m_pPopupMenu = new wxMenu();
	m_pEditCellSub = new wxMenu();

	m_pEditCellSub->Append((int)SSW::ID_CHANGE_CELL_BG_COLOUR, _T("&Background Colour"));
	m_pEditCellSub->Append((int)SSW::ID_CHANGE_CELL_FONT, _T("&Font"));
	m_pEditCellSub->Append((int)SSW::ID_CHANGE_CELL_SIZE, _T("&Size"));

	m_pPopupMenu->AppendSubMenu(m_pEditCellSub, _T("&Modify Cell..."));
}

void ExerciseGrid::SetupLabelArray()
{
	m_labels.Add(_T("Muscle Group"));
	m_labels.Add(_T("Exercise"));
	m_labels.Add(_T("Sets"));
	m_labels.Add(_T("Repetitions"));
	m_labels.Add(_T("Notes"));
}

void ExerciseGrid::SetupWorkoutTemplate()
{
	this->SetupTitle();

	m_currDay = 1;
	m_rowDayCoord = 4;

	for (auto i{ 0 }; i < 5; ++i)
	{
		this->SetupDayLabel();
	}
}

void ExerciseGrid::AddWorkoutDay()
{
	this->SetupDayLabel();
}

void ExerciseGrid::SetupTitle()
{
	// Set properties for the title so it looks nice and sizes correctly
	this->SetCellValue(wxGridCellCoords(0, 0), _T("Resistance Training Routine"));
	this->SetCellFont(0, 0, Fonts::GetBoldFont(20));
	this->SetCellSize(0, 0, 2, 5); // determine how many rows and cols the title will take
	this->SetCellBackgroundColour(0, 0, wxColour(255, 100, 100));
}

void ExerciseGrid::SetupDayLabel()
{
	this->SetCellValue(wxGridCellCoords(m_rowDayCoord, 0), wxString(_T("Day ")) << m_currDay); // write the day label
	this->SetCellFont(m_rowDayCoord, 0, Fonts::GetBoldFont(10)); // set the font for the day label

	// colour of cell which spans for 10 cols
	for (auto i{ m_rowDayCoord }; i < m_rowDayCoord + 10; ++i)
	{
		this->SetCellBackgroundColour(i, 0, wxColour(0, 150, 255));
	}

	// loop through the labels and set their background colours
	for (auto i{ 0 }; i < 5; ++i)
	{
		this->SetCellFont(m_rowDayCoord, i + 1, Fonts::GetBoldFont(8));
		this->SetCellValue(wxGridCellCoords(m_rowDayCoord, i + 1), m_labels[i]);
		this->SetCellBackgroundColour(m_rowDayCoord, i + 1, wxColour(0, 150, 255));
	}
	// with the exception of the notes label: change it to yellow
	this->SetCellBackgroundColour(m_rowDayCoord, 5, wxColour(255, 255, 0));

	// handle value updates
	++m_currDay;
	m_rowDayCoord += 11;

	// Check to ensure we have enough room on the grid
	// if not, add more rows
	if (m_rowDayCoord + 10 >= GetNumberRows() || m_rowDayCoord >= GetNumberRows())
		this->AppendRows(20, true);
}

void ExerciseGrid::OnUpdateCell(wxGridEvent& event)
{
	// Ensure there is a currently active or selected cell.
	if ( (m_currCell.GetCol() >= 0) && (m_currCell.GetRow() >= 0) )
	{
		int row = m_currCell.GetRow();
		int col = m_currCell.GetCol();

		m_currCellState = GridCellState(row, col, this->GetCellValue(row, col), this->GetCellFont(row, col), this->GetCellSize(wxGridCellCoords(row, col)), this->GetCellBackgroundColour(row, col));
	}
}

void ExerciseGrid::OnLeftClickCell(wxGridEvent& event)
{
	m_currCell = wxGridCellCoords(event.GetRow(), event.GetCol());
	this->SetGridCursor(m_currCell);
}

void ExerciseGrid::OnSelectCell(wxGridEvent& event)
{
	m_currCell = wxGridCellCoords(event.GetRow(), event.GetCol());
}

void ExerciseGrid::OnRightClickCell(wxGridEvent& event)
{
	m_currCell = wxGridCellCoords(event.GetRow(), event.GetCol()); // update cell coordinates

	this->PopupMenu(m_pPopupMenu);
}

void ExerciseGrid::OnChangeBackgroundColour(wxCommandEvent& event)
{
	wxColourDialog* pClrDlg = new wxColourDialog(this);
	pClrDlg->Show(true);

	if (pClrDlg->ShowModal() == wxID_OK)
	{
		wxColourData data = pClrDlg->GetColourData();
		wxColour colour = data.GetColour();

		this->SetCellBackgroundColour(m_currCell.GetRow(), m_currCell.GetCol(), colour);
	}
}

void ExerciseGrid::OnChangeCellFont(wxCommandEvent& event)
{
	m_pFontDlg = new wxFontDialog(this);
	m_pFontDlg->Show(true);

	if (m_pFontDlg->ShowModal() == wxID_OK)
	{
		wxFontData data = m_pFontDlg->GetFontData();
		wxFont font = data.GetChosenFont();

		this->SetCellFont(m_currCell.GetRow(), m_currCell.GetCol(), font);
		this->ForceRefresh();
	}
}

void ExerciseGrid::OnChangeCellSize(wxCommandEvent& event)
{
	m_pCCSD = new ChangeCellSizeDlg(this, wxID_ANY);
	m_pCCSD->Show(true);

	// pass the current row and col to the spin ctrls
	m_pCCSD->SetRow(m_currCell.GetRow());
	m_pCCSD->SetCol(m_currCell.GetCol());

	if (m_pCCSD->ShowModal() == wxID_OK)
	{
		this->SetCellSize(m_pCCSD->GetRow(), m_pCCSD->GetCol(), m_pCCSD->GetNumRows(), m_pCCSD->GetNumCols());
	}
}
