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
}

void SpreadsheetWindow::SetupMenu()
{
	m_pFileMenu = new wxMenu();
	m_pMenuBar = new wxMenuBar();

	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit"));

	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	this->SetMenuBar(m_pMenuBar);
}

void SpreadsheetWindow::SetupSizing()
{
	this->SetInitialSize(SSW_SIZE);
	this->SetMinSize(SSW_SIZE);
}

void SpreadsheetWindow::SetupControls()
{
	m_pGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pGrid->CreateGrid(100, 10); // Create a grid with 100 rows and 10 columns
}

void SpreadsheetWindow::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopSizer->Add(m_pGrid, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}