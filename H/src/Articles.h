#ifndef ARTICLES_H
#define ARTICLES_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/html/htmlwin.h>

class ArticleContainer : public wxPanel
{
public:
	ArticleContainer(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticleContainer();
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


	// events

};

#endif