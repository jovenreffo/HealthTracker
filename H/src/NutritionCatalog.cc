#include "NutritionCatalog.h"
#include "StandardPath.hpp"

// =================== CatalogItem ===================

CatalogItem::CatalogItem(const wxString& name, const wxBitmap& bmp, int calorieCount)
	: m_name{ name }, m_itemBmp{ bmp }, m_calorieCount{ calorieCount }
{

}

// =================== FoodList ===================

FoodList::FoodList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	this->Init();

	// Bind events
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &FoodList::OnRightClickItem, this);
	this->Bind(wxEVT_LIST_ITEM_ACTIVATED, &FoodList::OnDoubleClickItem, this);
}

FoodList::~FoodList()
{
	// Unbind events
	this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &FoodList::OnRightClickItem, this);
	this->Unbind(wxEVT_LIST_ITEM_ACTIVATED, &FoodList::OnDoubleClickItem, this);
}

void FoodList::Init()
{
	this->SetupMenu();
	this->SetupImageList();
}

void FoodList::SetupMenu()
{
	m_pMenu = new wxMenu();
}

void FoodList::SetupImageList()
{
	m_pImageList = new wxImageList(80, 80);


	this->AssignImageList(m_pImageList, wxIMAGE_LIST_NORMAL);
}

void FoodList::AddNutritionItem(const CatalogItem& info)
{

}

void FoodList::OnDoubleClickItem(wxListEvent& e)
{

}

void FoodList::OnRightClickItem(wxListEvent& e)
{
	this->PopupMenu(m_pMenu);
}

// =================== NutritionCatalog ===================

NutritionCatalog::NutritionCatalog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	this->SetBackgroundColour(wxColour(240, 240, 240));

	// Initialization handler
	this->Init();

#if wxUSE_STATUSBAR
	this->CreateStatusBar(1);
	this->SetStatusText(_T("No item selected."));
#endif
}

void NutritionCatalog::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void NutritionCatalog::SetupControls()
{
	m_pFoodList = new FoodList(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
}

void NutritionCatalog::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopSizer->Add(m_pFoodList, wxSizerFlags().Proportion(1).Expand());
}

void NutritionCatalog::SetupSizing()
{
#ifdef NC_SIZE
	this->SetInitialSize(NC_SIZE);
	this->SetMinSize(NC_SIZE);
#endif
}

