#include "Articles.h"
#include "StandardPath.hpp"
#include <wx/textctrl.h>

// add  preprocessor definition for the path so it doesn't have to be typed out
#define ARTICLE_IMG_PATH (path_data::dataDir + _T("\\Images\\Articles\\"))

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
	this->SetupImageList();
}

void ArticleList::SetupImageList()
{
	m_pImageList = new wxImageList(64, 64);

	this->AssignImageList(m_pImageList, wxIMAGE_LIST_NORMAL);
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

void ArticleList::AddArticleItem(const wxString& articleLink, const wxString& articleTitle, const wxBitmap& articleThumbnail)
{
	m_pImageList->Add(articleThumbnail);
	this->InsertItem(m_currentIndex, articleTitle, m_currentIndex);
}

void ArticleList::OnRightClickItem(wxListEvent& event)
{
}

void ArticleList::OnOpenLinkInBrowser(wxCommandEvent& event)
{
}

// ArticleContainer

ArticleContainer::ArticleContainer(const wxString& which, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style), m_which{ which }
{
	this->InitializeList();
	this->SetupSizer();

	this->SetBackgroundColour(*wxWHITE);
}

ArticleContainer::~ArticleContainer()
{
}

void ArticleContainer::InitializeList()
{
	m_pArticleList = new ArticleList(m_which, this, wxID_ANY);
	
}

void ArticleContainer::SetupSizer()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pTopSizer->Add(m_pArticleList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

// ArticleNotebook

ArticleNotebook::ArticleNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxNotebook(parent, id, pos, size, style)
{
	this->Init();
}

ArticleNotebook::~ArticleNotebook()
{
	this->DestroyChildren();
}

void ArticleNotebook::Init()
{
	this->SetupControls();
	this->SetupSizer();
	this->SetupNotebook();
}

void ArticleNotebook::SetupControls()
{
	// Parent panels
	m_pFitnessContainer = new wxPanel(this, wxID_ANY);
	m_pFocusContainer = new wxPanel(this, wxID_ANY);
	m_pNutritionContainer = new wxPanel(this, wxID_ANY);
	
	// Lists
	m_pFitnessArtList = new ArticleList(_T("Health && Fitness"), m_pFitnessContainer, wxID_ANY);
	m_pFocusArtList = new ArticleList(_T("Focus && Productivity"), m_pFocusContainer, wxID_ANY);
	m_pNutritionArtList = new ArticleList(_T("Food && Nutrition"), m_pNutritionContainer, wxID_ANY);

}

void ArticleNotebook::SetupSizer()
{
	// Initialize
	m_pFitnessSizer = new wxBoxSizer(wxVERTICAL);
	m_pFocusSizer = new wxBoxSizer(wxVERTICAL);
	m_pNutrSizer = new wxBoxSizer(wxVERTICAL);

	// Set
	m_pFitnessContainer->SetSizerAndFit(m_pFitnessSizer);
	m_pFocusContainer->SetSizerAndFit(m_pFocusSizer);
	m_pNutritionContainer->SetSizerAndFit(m_pNutrSizer);

	// Add
	m_pFitnessSizer->Add(m_pFitnessArtList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pFocusSizer->Add(m_pFocusArtList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pNutrSizer->Add(m_pNutritionArtList, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));

}


void ArticleNotebook::SetupNotebook()
{
	// Set up the image list
	m_pImageList = new wxImageList(30, 30);

	m_fitnessBmp = wxBitmap(path_data::dataDir + _T("\\Images\\Articles\\run.png"), wxBITMAP_TYPE_PNG);
	m_focusBmp = wxBitmap(path_data::dataDir + _T("\\Images\\Articles\\growth.png"), wxBITMAP_TYPE_PNG);
	m_nutritionBmp = wxBitmap(path_data::dataDir + _T("\\Images\\nutrition.png"), wxBITMAP_TYPE_PNG);

	m_pImageList->Add(m_fitnessBmp);
	m_pImageList->Add(m_focusBmp);
	m_pImageList->Add(m_nutritionBmp);
	this->AssignImageList(m_pImageList);

	// Add pages
	this->AddPage(m_pFitnessContainer, _T("Health && Fitness"), true, 0);
	this->AddPage(m_pFocusContainer, _T("Focus && Productivity"), false, 1);
	this->AddPage(m_pNutritionContainer, _T("Food && Nutrition"), false, 2);
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
	m_pArticleNotebook = new ArticleNotebook(this, wxID_ANY);
	this->SetupSizers();
}


void ArticlePanel::SetupSizers()
{
	// Initialize the top sizer
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopSizer->Add(m_pArticleNotebook, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

