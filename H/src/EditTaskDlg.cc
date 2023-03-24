#include "EditTaskDlg.h"

EditTaskDlg::EditTaskDlg(const wxString& taskName, const wxString& taskDesc, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_taskName{ taskName }, m_taskDesc{ taskDesc }
{
	// Set the title to include the current taske name
	this->SetTitle(wxString(_T("Edit Task - ")) << m_taskName);

	this->Init();

	// Event binding
}

EditTaskDlg::~EditTaskDlg()
{
	// Unbind events
}

void EditTaskDlg::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void EditTaskDlg::SetupControls()
{

}

void EditTaskDlg::SetupSizers()
{

}

void EditTaskDlg::SetupSizing()
{
	this->SetMinSize(ETD_SIZE);
	this->SetInitialSize(ETD_SIZE);
}