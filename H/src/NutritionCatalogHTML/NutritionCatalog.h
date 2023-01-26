#ifndef NUTRITIONCATALOG_H
#define NUTRITIONCATALOG_H

#include <wx/wx.h>
#include <wx/html/htmlwin.h>
#include <wx/wxhtml.h>

class NutritionCatalog : public wxHtmlWindow
{
public:
	NutritionCatalog(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxHW_DEFAULT_STYLE);
};

#endif