#include "NutritionPanel.h"

NutritionPanel::NutritionPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void NutritionPanel::Init()
{
	this->SetupNutritionBook();
	this->SetupSizers();
}

void NutritionPanel::SetupNutritionBook()
{
	m_pNutrBook = new NutritionBook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
	m_pNutrBook->Show(true);
}

void NutritionPanel::SetupSizers()
{
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pBoxSizer);
	
	// add any elements
	m_pBoxSizer->Add(m_pNutrBook, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}
