#ifndef ARTICLES_H
#define ARTICLES_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/clipbrd.h>

class ArticleContainer : public wxPanel
{
private:
	// a list view and a string array for holding the links of each article
	// when an item from m_pArticleList is double clicked or Right click -> Open, the prgram will launch the default browser and pass in the link
	wxListView* m_pArticleList;
	wxArrayString m_articleLinkArr;

	// wxMenu for when m_pArticleList is right clicked and actions must be displayed
	wxMenu* m_pMenu;

public:
	ArticleContainer(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticleContainer();

	// Member and general setup for article list
	void InitializeList();
	void SetupMenu();
	void AddArticleItem(const wxString& articleLink, const wxString& articleTitle, const wxBitmap& articleThumbnail);

	// Events
	void OnRightClickItem(wxListEvent& event);
	void OnOpenArticle(wxCommandEvent& event);
	void OnCopyArticleLink(wxCommandEvent& event);
};

// === ArticlePanel ===

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