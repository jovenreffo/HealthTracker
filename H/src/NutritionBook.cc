#include "NutritionBook.h"
#include "StandardPath.hpp"

BEGIN_EVENT_TABLE(NutritionBook, wxNotebook)

END_EVENT_TABLE()

NutritionBook::NutritionBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxNotebook(parent, id, pos, size, style)
{
}

NutritionBook::~NutritionBook()
{
}

void NutritionBook::Init()
{
}

void NutritionBook::SetupImageList()
{
	m_pImageList = new wxImageList(30, 30);

	this->AssignImageList(m_pImageList);
}
