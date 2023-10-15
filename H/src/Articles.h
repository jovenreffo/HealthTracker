#ifndef ARTICLES_H
#define ARTICLES_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/sizer.h>

class ArticleHtmlPanel : public wxPanel
{
private:
	wxString m_filePath;

public:
	ArticleHtmlPanel(const wxString& htmlFilePath,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticleHtmlPanel();
};

class ArticlePanel : public wxPanel
{
private:
	// sizers for different article sections
	wxFlexGridSizer* m_pTopSizer;
	wxStaticBoxSizer* m_pFitnessSizer;
	wxStaticBoxSizer* m_pFocusSizer; // productivity & focus
	wxStaticBoxSizer* m_pNutritionSizer;


	// the static box from the sizers to be used as parents


public:
	ArticlePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticlePanel();

	// setup
	void SetupArticlePanel();

	void SetupFitnessArticlePanel();
	void SetupFocusArticlePanel();
	void SetupNutritionArticlePanel();
	void SetupSizers();

	// actions
	void AddArticle(const wxBitmap& bmp, const wxString& link, const wxString& articleTitle);

	// events

};

#endif