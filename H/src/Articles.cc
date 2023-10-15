#include "Articles.h"


ArticleHtmlPanel::ArticleHtmlPanel(const wxString& htmlFilePath, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style), m_filePath{ htmlFilePath }
{
}

ArticleHtmlPanel::~ArticleHtmlPanel()
{
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

void ArticlePanel::SetupFitnessArticlePanel()
{
}

void ArticlePanel::SetupFocusArticlePanel()
{
}

void ArticlePanel::SetupNutritionArticlePanel()
{
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

	m_pTopSizer->Add(m_pFitnessSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pFocusSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pNutritionSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

void ArticlePanel::AddArticle(const wxBitmap& bmp, const wxString& link, const wxString& articleTitle)
{
}
