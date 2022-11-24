#include "CaloriePanel.h"

BEGIN_EVENT_TABLE(CaloriePanel, wxPanel)
	EVT_BUTTON(static_cast<int>(C::ID_NEW_ITEM), CaloriePanel::OnNewItem)
END_EVENT_TABLE()

CaloriePanel::CaloriePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void CaloriePanel::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void CaloriePanel::SetupListView()
{
	m_pListView->AppendColumn(_T("Food/Item"));
	m_pListView->AppendColumn(_T("Calories"));
}

void CaloriePanel::SetupControls()
{
	m_pListView = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	this->SetupListView();

	m_pAddButton = new wxButton(this, static_cast<int>(C::ID_NEW_ITEM), _T("Add Item"), wxDefaultPosition, wxDefaultSize);
}

void CaloriePanel::SetupSizers()
{
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pBoxSizer);

	m_pBoxSizer->Add(m_pListView, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pBoxSizer->Add(m_pAddButton, wxSizerFlags().Proportion(0).Border(wxALL, 5));
}

// Events

void CaloriePanel::OnNewItem(wxCommandEvent& event)
{

}