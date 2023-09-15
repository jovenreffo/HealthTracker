#include <wx/statline.h>
#include "ClientPanel.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"

// === ClientList === 

ClientList::ClientList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->SetupList();
}

void ClientList::SetupList()
{
	this->SetupImageList();
	this->SetupMenu();
	this->SetupColumn();
	this->SetListFont();
}

void ClientList::SetupColumn()
{
	this->AppendColumn(_T("Clients"));
	this->SetColumnWidth(0, 400);
}

void ClientList::SetupImageList()
{
	m_pImageList = new wxImageList(23, 23);

	m_clientIconBmp = wxBitmap(path_data::dataDir + _T("\\Images\\clients_small.png"), wxBITMAP_TYPE_PNG);

	m_pImageList->Add(m_clientIconBmp);
	this->AssignImageList(m_pImageList, wxIMAGE_LIST_SMALL);
}

void ClientList::SetupMenu()
{
	m_pMenu = new wxMenu();
}

void ClientList::SetListFont()
{
	m_font = Fonts::GetBoldFont(15);
}

void ClientList::AddItem(const wxString& name)
{
	this->InsertItem(0, name, 0);
	this->SetItemFont(0, m_font);
}

// === ClientPanel === 

ClientPanel::ClientPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->InitClientPanel();

	// Bind events
}

ClientPanel::~ClientPanel()
{
	// Unbind events
}

void ClientPanel::InitClientPanel()
{
	this->SetupMemberControls();
	this->SetupSizers();
}

void ClientPanel::SetupMemberControls()
{
	// Set up an add button with a '+' icon.
	wxBitmap addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_pAddClientBtn = new wxButton(this, wxID_ANY, _T("Add New Client"));
	m_pAddClientBtn->SetBitmap(addBmp);

	m_pClientList = new ClientList(this, wxID_ANY);
}

void ClientPanel::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pTopButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	// Top button sizer
	m_pTopButtonSizer->Add(m_pAddClientBtn, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(m_pTopButtonSizer);

	// add a separator
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pClientList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}
