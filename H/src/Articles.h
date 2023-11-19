#ifndef ARTICLES_H
#define ARTICLES_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/clipbrd.h>

class ArticleList : public wxListView
{
private:
	wxMenu* m_pMenu;
	wxArrayString m_articleLinksArr;
	wxString m_listTitle;
	wxBoxSizer* m_pTopSizer;

public:
	// setup
	ArticleList(const wxString& which,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT);
	~ArticleList();

	void InitializeArticleList();
	void SetupMenu();
	void SetupList();
	void SetupSizer();

	// actions
	void AddArticleItem(const wxString& articleLink, const wxString& articleTitle, const wxBitmap& articleThumbnail);

	// events
	void OnRightClickItem(wxListEvent& event);
};

class ArticleContainer : public wxPanel
{
private:
	// a list view and a string array for holding the links of each article
	// when an item from m_pArticleList is double clicked or Right click -> Open, the prgram will launch the default browser and pass in the link
	ArticleList* m_pArticleList;

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
	
	// Getter
	const ArticleList* GetArticleList() { return m_pArticleList; }

	// Events
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
	ArticleContainer* m_pFitnessContainer;
	ArticleContainer* m_pFocusContainer;
	ArticleContainer* m_pNutritionContainer;

public:
	ArticlePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticlePanel();

	// setup
	void SetupArticlePanel();

	// setup for article containers
	void SetupContainers();
	void SetupFitnessContainer();
	void SetupFocusContainer();
	void SetupNutritionContainer();

	void SetupSizers();


	// events

};

#endif