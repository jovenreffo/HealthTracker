#ifndef NUTRITIONCATALOG_H
#define NUTRITIONCATALOG_H

#include <wx/wx.h>
#include <wx/html/htmlwin.h>
#include <wx/wxhtml.h>

#define NC_SIZE (wxSize(640, 480))

class NutritionCatalog : public wxFrame
{
private:
	wxHtmlWindow* m_pHtmlWindow;

public:
	NutritionCatalog(wxWindow* parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = NC_SIZE,
		long style = wxDEFAULT_FRAME_STYLE);

	void Init();
	void SetupSizing();

};

#endif