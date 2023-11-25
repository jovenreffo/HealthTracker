#include "Articles.h"
#include "StandardPath.hpp"

// ArticleList

ArticleList::ArticleList(const wxString& which, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style), m_listTitle{ which }
{
	this->InitializeArticleList();

	// Bind events
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &ArticleList::OnRightClickItem, this);
	m_pMenu->Bind(wxEVT_MENU, &ArticleList::OnOpenLinkInBrowser, this, wxID_OPEN);
}

ArticleList::~ArticleList()
{
	// unbind

}

void ArticleList::InitializeArticleList()
{
	this->SetupMenu();
	this->SetupList();
	this->SetupSizer();
}

void ArticleList::SetupMenu()
{
	m_pMenu = new wxMenu();
	m_pMenu->Append(wxID_OPEN, _T("Open in browser"));
}

void ArticleList::SetupList()
{
	this->AppendColumn(m_listTitle);
}

void ArticleList::SetupSizer()
{
}

void ArticleList::AddArticleItem(const wxString& articleLink, const wxString& articleTitle, const wxBitmap& articleThumbnail)
{
}

void ArticleList::OnRightClickItem(wxListEvent& event)
{
}

void ArticleList::OnOpenLinkInBrowser(wxCommandEvent& event)
{
}

// ArticleContainer

ArticleContainer::ArticleContainer(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->InitializeList();

	this->SetBackgroundColour(*wxWHITE);
}

ArticleContainer::~ArticleContainer()
{
}

void ArticleContainer::InitializeList()
{
	ArticleList* m_pArticleList;
}


// ArticlePanel

ArticlePanel::ArticlePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->SetupArticlePanel();
}

ArticlePanel::~ArticlePanel()
{

}

void ArticlePanel::SetupArticlePanel()
{
	// setup individual HTML windows
	this->SetupContainers();

	this->SetupSizers();
}

void ArticlePanel::SetupContainers()
{
	this->SetupFitnessContainer();
	this->SetupFocusContainer();
	this->SetupNutritionContainer();
}

void ArticlePanel::SetupFitnessContainer()
{
	m_pFitnessContainer = new ArticleContainer(this, wxID_ANY);
}

void ArticlePanel::SetupFocusContainer()
{
	m_pFocusContainer = new ArticleContainer(this, wxID_ANY);

}

void ArticlePanel::SetupNutritionContainer()
{
	m_pNutritionContainer = new ArticleContainer(this, wxID_ANY);

}

void ArticlePanel::SetupSizers()
{
	// Initialize the top sizer
	m_pTopSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	this->SetSizerAndFit(m_pTopSizer);

	// Sizers that will be 'containers' for articles
	m_pFitnessSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("Fitness"));
	m_pFocusSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("Productivity && Focus")); // use double ampersands because wxwidgets treats a single one as an accelerator
	m_pNutritionSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("Food && Nutrition"));

	// add containers to sizers
	m_pFitnessSizer->Add(m_pFitnessContainer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pFocusSizer->Add(m_pFocusContainer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pNutritionSizer->Add(m_pNutritionContainer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));


	// add all sizers to the main sizer
	m_pTopSizer->Add(m_pFitnessSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pFocusSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pNutritionSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}
