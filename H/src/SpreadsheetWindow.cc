#include <wx/config.h>
#include "SpreadsheetWindow.h"

SpreadsheetWindow::SpreadsheetWindow(wxWindow* parent,
	wxWindowID id,
	const wxString& title,
	const wxPoint& pos,
	const wxSize& size,
	long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	this->Init();
}

SpreadsheetWindow::~SpreadsheetWindow()
{
	// Unbind events
	m_pFileMenu->Unbind(wxEVT_MENU, &SpreadsheetWindow::OnExit, this, wxID_EXIT);
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

void SpreadsheetWindow::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupMenu();
	this->SetupSizing();

	this->BindEvents();
}

void SpreadsheetWindow::SetupMenu()
{
	m_pFileMenu = new wxMenu();
	m_pInsertMenu = new wxMenu();
	m_pMenuBar = new wxMenuBar();

	// File menu
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit"));

	// Insert menu


	// Menubar
	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	m_pMenuBar->Append(m_pInsertMenu, _T("&Insert"));
	this->SetMenuBar(m_pMenuBar);
}

void SpreadsheetWindow::SetupSizing()
{
	this->SetInitialSize(SSW_SIZE);
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

void SpreadsheetWindow::BindEvents()
{
	// Menu events
	m_pFileMenu->Bind(wxEVT_MENU, &SpreadsheetWindow::OnExit, this, wxID_EXIT);
}

// Events

void SpreadsheetWindow::OnExit(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to exit?"), _T("Confirm"), wxYES_NO | wxICON_WARNING) == wxYES)
		this->Close(true);
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
