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
	this->SetupSizing();
	this->SetupControls();
	this->SetupSizers();
}

void SpreadsheetWindow::SetupSizing()
{

}

void SpreadsheetWindow::SetupControls()
{

}

void SpreadsheetWindow::SetupSizers()
{

}