#ifndef _CALORIEBOOK_H_
#define _CALORIEBOOK_H_

#include <wx/notebook.h>

class NutritionBook: public wxNotebook
{
private:
	DECLARE_EVENT_TABLE()

public:
	NutritionBook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);

	~NutritionBook();
};

#endif