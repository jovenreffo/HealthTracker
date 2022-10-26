#include "Window.h"

// Event table
BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_EXIT, Frame::OnExit)

END_EVENT_TABLE()

Frame::Frame()
	: wxFrame{ nullptr, -1, _T("Health Trackr"), wxDefaultPosition, WINDOW_SIZE }
{
	this->Init();
}

void Frame::Init()
{
	this->SetupMenuBar();
	this->SetupSizes();
	this->SetupListbook();
}

// Window setup

void Frame::SetupMenuBar()
{
	m_pMenuBar = new wxMenuBar();
	m_pFileMenu = new wxMenu();

	// File menu
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Exit\tAlt+F4"));

	m_pMenuBar->Append(m_pFileMenu, _T("&File"));
	this->SetMenuBar(m_pMenuBar);
}

void Frame::SetupSizes()
{
	this->SetInitialSize(WINDOW_SIZE);
	this->SetMinSize(WINDOW_SIZE);
}

void Frame::SetupListbook()
{
	m_pListbook = new Listbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_TOP);
	m_pListbook->Show(true);
}

// Events

void Frame::OnExit(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to exit?"), _T("Confirm"), wxYES_NO | wxICON_WARNING) == wxYES)
		this->Close(true);
}