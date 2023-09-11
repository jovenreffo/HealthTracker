#include "ClientPanel.h"

// === ClientList === 

ClientList::ClientList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
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
}

void ClientPanel::SetupSizers()
{
}
