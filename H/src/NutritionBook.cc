#include "NutritionBook.h"

BEGIN_EVENT_TABLE(NutritionBook, wxNotebook)

END_EVENT_TABLE()

NutritionBook::NutritionBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxNotebook(parent, id, pos, size, style)
{
}

NutritionBook::~NutritionBook()
{
}
