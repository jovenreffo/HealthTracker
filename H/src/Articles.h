#ifndef ARTICLES_H
#define ARTICLES_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/clipbrd.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <utility>


class ArticleList : public wxListView
{
private:
	// List members
	wxMenu* m_pMenu;
	wxArrayString m_articleLinksArr;
	wxString m_listTitle;

	// Image list
	wxImageList* m_pImageList;
	int m_currentIndex{ 0 };

	// sizer
	wxBoxSizer* m_pTopSizer;

public:
	// setup
	ArticleList(const wxString& which,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_ICON);
	~ArticleList();

	void InitializeArticleList();
	void SetupImageList();
	void SetupMenu();
	void SetupList();

	// actions
	void AddArticleItem(const wxString& articleLink, const wxString& articleTitle, const wxBitmap& articleThumbnail);

	// events
	void OnRightClickItem(wxListEvent& event);
	void OnOpenLinkInBrowser(wxCommandEvent& event); // for m_pMenu
};

class ArticleContainer : public wxPanel
{
private:
	// a list view and a string array for holding the links of each article
	// when an item from m_pArticleList is double clicked or Right click -> Open, the prgram will launch the default browser and pass in the link
	ArticleList* m_pArticleList;
	wxString m_which;

	// sizer
	wxBoxSizer* m_pTopSizer;

public:
	ArticleContainer(const wxString& which,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticleContainer();

	// Member and general setup for article list
	void InitializeList();
	void SetupSizer();

	
	// Getter
	ArticleList* GetArticleList() { return m_pArticleList; }
};

// === ArticleNotebook ===

class ArticleNotebook : public wxNotebook
{
private:
	// Article panels
	wxPanel* m_pFitnessContainer;
	wxPanel* m_pFocusContainer;
	wxPanel* m_pNutritionContainer;
	// Article lists
	ArticleList* m_pFitnessArtList;
	ArticleList* m_pFocusArtList;
	ArticleList* m_pNutritionArtList;
	// Article sizers
	wxBoxSizer* m_pFitnessSizer;
	wxBoxSizer* m_pFocusSizer;
	wxBoxSizer* m_pNutrSizer;;

	// Notebook members
	wxImageList* m_pImageList;
	wxBitmap m_fitnessBmp;
	wxBitmap m_focusBmp;
	wxBitmap m_nutritionBmp;

public:
	ArticleNotebook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	~ArticleNotebook();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizer();
	void SetupNotebook();
};

// === ArticlePanel ===

class ArticlePanel : public wxPanel
{
private:
	// sizers 
	wxBoxSizer* m_pTopSizer;

	// Article notebook
	ArticleNotebook* m_pArticleNotebook;

public:
	ArticlePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticlePanel();

	// setup
	void SetupArticlePanel();

	// sizers & splitters
	void SetupSizers();

	// events

};

#endif