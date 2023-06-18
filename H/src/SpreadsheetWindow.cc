#include <wx/config.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/valgen.h>
#include "SpreadsheetWindow.h"

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
	m_pCancel = new wxButton(this, wxID_OK, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
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

	return true;
}

void SpreadsheetWindow::BindEvents()
{
	// Menu events
	m_pFileMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnExit, this, wxID_EXIT);
	m_pInsertMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnAddCol, this, (int)SSW::ID_INSERT_COL);
	m_pInsertMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnAddRow, this, (int)SSW::ID_INSERT_ROW);
}

void SpreadsheetWindow::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupMenu();
	this->SetupSizing();
}

void SpreadsheetWindow::SetupMenu()
{
	m_pFileMenu = new wxMenu();
	m_pExportSubMenu = new wxMenu();
	m_pInsertMenu = new wxMenu();
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

	// Menubar
	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pInsertMenu, _T("&Insert"));
	this->SetMenuBar(m_pMenuBar);
}

void SpreadsheetWindow::SetupSizing()
{
	wxSize size = this->GetBestSize();
	wxSize initial = wxSize(size.x + 50, 480);

	this->SetInitialSize(initial);
	this->SetMinSize(SSW_SIZE);
}

void SpreadsheetWindow::SetupControls()
{
	m_pGrid = new ExerciseGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
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

// ===== ExerciseGrid ======

ExerciseGrid::ExerciseGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxGrid(parent, id, pos, size, style)
{
	this->CreateGrid(100, 10); // Create a grid with 100 rows and 10 columns

	this->Init();
}

void ExerciseGrid::Init()
{
	this->SetupConfig();
}

void ExerciseGrid::SetupConfig()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	if (pConfig == nullptr)
		return;

	pConfig->SetPath(_T("/Preferences/"));

	if (pConfig->Read(_T("CheckFont"), 0L) == 1L)
	{
		for (auto rows{ 0 }; rows < this->GetNumberRows(); ++rows)
		{
			for (auto cols{ 0 }; cols < this->GetNumberCols(); ++cols)
			{
				this->SetCellFont(rows, cols, wxFont(
					pConfig->Read("FontSize", 10L),
					static_cast<wxFontFamily>(pConfig->Read("FontFamily", static_cast<long>(wxFONTFAMILY_DEFAULT))),
					static_cast<wxFontStyle>(pConfig->Read("FontStyle", static_cast<long>(wxFONTSTYLE_NORMAL))),
					wxFONTWEIGHT_NORMAL,
					pConfig->Read("FontUnderline", 0L),
					pConfig->Read("FaceName", "")
				));
			}
		}
	}
}
