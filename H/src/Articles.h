#ifndef ARTICLES_H
#define ARTICLES_H

#include <wx/wx.h>
#include <wx/panel.h>

class ArticlePanel : public wxPanel
{
public:
	ArticlePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
	~ArticlePanel();


};

#endif