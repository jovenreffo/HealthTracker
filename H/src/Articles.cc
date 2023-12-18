#include "Articles.h"
#include "StandardPath.hpp"

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

// ArticleNotebook

ArticleNotebook::ArticleNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
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
	this->SetupPanels();
	this->SetupSizer();
	this->SetupNotebook();
}

void ArticleNotebook::SetupControls()
{
}

void ArticleNotebook::SetupPanels()
{
}

void ArticleNotebook::SetupSizer()
{
}

void ArticleNotebook::SetupNotebook()
{
	m_pImageList = new wxImageList(26, 26);

	this->AssignImageList(m_pImageList);
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
	this->SetupSizers();
}


void ArticlePanel::SetupSizers()
{
	// Initialize the top sizer
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);
}

