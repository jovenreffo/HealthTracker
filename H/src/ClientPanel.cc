#include <wx/statline.h>
#include <wx/valgen.h>
#include "ClientPanel.h"
#include "StandardPath.hpp"
#include "Font/Font.hpp"

// === ClientSchedule ===

ClientSchedule::ClientSchedule(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->SetupList();
	
	// Bind events

}

ClientSchedule::~ClientSchedule()
{
	// unbind events
}

void ClientSchedule::SetupList()
{
	this->SetupColumns();
	this->SetupImageList();
	this->SetupMenu();
	this->SetListFont();
}

void ClientSchedule::SetupColumns()
{
	// push all the days of the week into an array string
	m_daysOfWeekStr.push_back(_T("Sunday"));
	m_daysOfWeekStr.push_back(_T("Monday"));
	m_daysOfWeekStr.push_back(_T("Tuesday"));
	m_daysOfWeekStr.push_back(_T("Wednesday"));
	m_daysOfWeekStr.push_back(_T("Thursday"));
	m_daysOfWeekStr.push_back(_T("Friday"));
	m_daysOfWeekStr.push_back(_T("Saturday"));

	// loop through the array string and add columns
	for (auto i{ 0 }; i < m_daysOfWeekStr.size(); ++i)
	{
		this->AppendColumn(m_daysOfWeekStr[i]);
	}
}

void ClientSchedule::SetupImageList()
{
}

void ClientSchedule::SetupMenu()
{
}

void ClientSchedule::SetListFont()
{
	m_font = Fonts::GetBoldFont(11);
}

void ClientSchedule::OnRightClickItem(wxListEvent& event)
{
}


// === NewClientDlg ===

NewClientDlg::NewClientDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->SetupNewClientDlg();

	// Bind events
	m_pOk->Bind(wxEVT_BUTTON, &NewClientDlg::OnOK, this);
	m_pCancel->Bind(wxEVT_BUTTON, &NewClientDlg::OnCancel, this);
}

NewClientDlg::~NewClientDlg()
{
	// unbind
	m_pOk->Unbind(wxEVT_BUTTON, &NewClientDlg::OnOK, this);
	m_pCancel->Unbind(wxEVT_BUTTON, &NewClientDlg::OnCancel, this);
}

void NewClientDlg::SetupNewClientDlg()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void NewClientDlg::SetupControls()
{
	m_pClientNameTxt = new wxTextCtrl(this, wxID_ANY);
	m_pNumSessionsCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 1, 7, 1);
	m_pClientNameTxt->SetValidator(wxGenericValidator(&m_clientName));
	m_pNumSessionsCtrl->SetValidator(wxGenericValidator(&m_numSessions));

	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"));
}

void NewClientDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pControlSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	this->SetSizerAndFit(m_pTopSizer);

	// Controls
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Client Name:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pClientNameTxt, wxSizerFlags().Border(wxALL, 5).Expand());
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Sessions per week:")), wxSizerFlags().Border(wxALL, 5));
	m_pControlSizer->Add(m_pNumSessionsCtrl, wxSizerFlags().Border(wxALL, 5).Expand());
	m_pTopSizer->Add(m_pControlSizer, wxSizerFlags().CentreHorizontal());

	// Button sizer + static line
	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
}

void NewClientDlg::SetupSizing()
{
	wxSize size{ this->GetBestSize() };
	this->SetMinSize(size);
	this->SetInitialSize(wxSize(size.GetX() + 50, size.GetY() + 35));
}

void NewClientDlg::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void NewClientDlg::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

// === ClientList === 

ClientList::ClientList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->SetupList();
	
	// Bind events
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &ClientList::OnRightClickItem, this);
	m_pMenu->Bind(wxEVT_MENU, &ClientList::OnRemoveClient, this, wxID_REMOVE);
}

ClientList::~ClientList()
{
	this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &ClientList::OnRightClickItem, this);
	m_pMenu->Unbind(wxEVT_MENU, &ClientList::OnRemoveClient, this, wxID_REMOVE);
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
	this->AppendColumn(_T("Sessions per week"));
	this->SetColumnWidth(0, 100); // Set the column width for list of client's names
	this->SetColumnWidth(1, 125); // Width for num sessions
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

	m_pMenu->Append(wxID_REMOVE, _T("Remove Client"));
}

void ClientList::SetListFont()
{
	m_font = Fonts::GetBoldFont(15);
}

void ClientList::AddItem(const wxString& name, int sessions)
{
	// Add the client name
	this->InsertItem(0, name, 0);
	this->SetItemFont(0, m_font);

	// Add how many sessions they are doing per week
	this->SetItem(0, 1, std::to_string(sessions), -1);
}

void ClientList::OnRightClickItem(wxListEvent& event)
{
	this->PopupMenu(m_pMenu);
}

void ClientList::OnRemoveClient(wxCommandEvent& event)
{
	int selected = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

	if (wxMessageBox(_T("Are you sure you want to delete this client and all of their associated progress?"), _T("Confirm"), wxYES_NO | wxICON_EXCLAMATION) == wxYES)
		this->DeleteItem(selected);
}

// === ClientPanel === 

ClientPanel::ClientPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->InitClientPanel();

	// Bind events
	m_pAddClientBtn->Bind(wxEVT_BUTTON, &ClientPanel::OnAddClient, this);
}

ClientPanel::~ClientPanel()
{
	// Unbind events
	m_pAddClientBtn->Unbind(wxEVT_BUTTON, &ClientPanel::OnAddClient, this);

}

void ClientPanel::InitClientPanel()
{
	this->SetupSplitterWin();
	this->SetupMemberControls();
	this->SetupSizers();
}

void ClientPanel::SetupClientListPanel()
{
	m_pClientListPanel = new wxPanel(m_pSplitterWin);
	m_pClientSchedPanel = new wxPanel(m_pSplitterWin);

	// Initialize the client schedule and panel
	m_pClientList = new ClientList(m_pClientListPanel, wxID_ANY);
	m_pClientSchedule = new ClientSchedule(m_pClientSchedPanel, wxID_ANY);
}

void ClientPanel::SetupMemberControls()
{
	// Set up an add button with a '+' icon.
	wxBitmap addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_pAddClientBtn = new wxButton(this, wxID_ANY, _T("Add New Client"));
	m_pAddClientBtn->SetBitmap(addBmp);

	this->SetupClientListPanel();
}

void ClientPanel::SetupSplitterWin()
{
	m_pSplitterWin = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH | wxSP_LIVE_UPDATE | wxSP_NOBORDER);
	m_pSplitterWin->SetSashGravity(0.3); // slight resize bias to the schedule window as it requires more space
	m_pSplitterWin->SetMinimumPaneSize(100);
	m_pSplitterWin->SetSashPosition(15, true);
}

void ClientPanel::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pClientListSizer = new wxBoxSizer(wxVERTICAL);
	m_pClientSchedSizer = new wxBoxSizer(wxVERTICAL);
	m_pTopButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	
	this->SetSizerAndFit(m_pTopSizer);
	m_pClientListPanel->SetSizerAndFit(m_pClientListSizer);
	m_pClientSchedPanel->SetSizerAndFit(m_pClientSchedSizer);

	// add list to list sizer
	m_pClientListSizer->Add(m_pClientList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pClientSchedSizer->Add(m_pClientSchedule, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));

	// Split the window
	m_pSplitterWin->SplitVertically(m_pClientListPanel, m_pClientSchedPanel);

	// Top button sizer
	m_pTopButtonSizer->Add(m_pAddClientBtn, wxSizerFlags().Border(wxALL, 5));
	m_pTopSizer->Add(m_pTopButtonSizer);

	// add a separator
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pSplitterWin, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

void ClientPanel::OnAddClient(wxCommandEvent& event)
{
	m_pNewClientDlg = new NewClientDlg(this, wxID_ANY);
	m_pNewClientDlg->Show(true);

	if (m_pNewClientDlg->ShowModal() == wxID_OK)
	{
		m_pClientList->AddItem(m_pNewClientDlg->GetClientName(), m_pNewClientDlg->GetNumSessions());
	}
}