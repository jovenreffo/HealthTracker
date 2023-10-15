#ifndef ARTICLES_H
#define ARTICLES_H

#include <wx/wx.h>
#include <wx/panel.h>

class ArticleHtmlPanel : public wxPanel
{
public:
	ArticleHtmlPanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticleHtmlPanel();
};

class ArticlePanel : public wxPanel
{
public:
	ArticlePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticlePanel();

	// setup
	void SetupArticlePanel();

	// actions
	void AddArticle(const wxBitmap& bmp, const wxString& link, const wxString& articleTitle);

	// events

};

#endif