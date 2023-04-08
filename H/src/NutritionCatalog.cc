#include "NutritionCatalog.h"
#include "StandardPath.hpp"

// =================== ItemViewer ===================

#define IV_DLG_SIZE (wxSize(300, 300))
#define IV_DLG_SIZE_MAX (wxSize())

class ItemViewer : public wxDialog
{
private:
	wxBoxSizer* m_pTopSizer;

public:
	ItemViewer(wxWindow* parent,
		wxWindowID id = -1,
		const wxString& title = _T("View Nutrition Item"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX)
		: wxDialog(parent, id, title, pos, size, style)
	{
		this->Init();
	}

	~ItemViewer() {}

	void Init()
	{
		this->SetupSizers();
		this->SetupSizing();
	}

	void SetupSizers()
	{

	}

	void SetupSizing()
	{
		this->SetInitialSize(IV_DLG_SIZE);
		this->SetMinSize(IV_DLG_SIZE);
		this->SetMaxSize(IV_DLG_SIZE_MAX);
	}
};

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

	wxBitmap egg = wxBitmap(path_data::dataDir + _T("\\Images\\nutrition\\eggs.png"), wxBITMAP_TYPE_PNG);
	CatalogItem ci("eggs", egg, 60);
	this->AddNutritionItem(ci);

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

	m_pMenu->Append(wxID_OPEN, _T("&Open Item"));
}

void FoodList::SetupImageList()
{
	m_pImageList = new wxImageList(80, 80);


	this->AssignImageList(m_pImageList, wxIMAGE_LIST_NORMAL);
}

void FoodList::AddNutritionItem(const CatalogItem& info)
{
	//m_pCatalogItems->push_back(info);

	wxString name = info.GetName();
	wxBitmap bmp = info.GetBmp();

	m_pImageList->Add(bmp);
	this->InsertItem(0, name);
	this->SetItemImage(0, 0);
}

void FoodList::OnDoubleClickItem(wxListEvent& e)
{

}

void FoodList::OnRightClickItem(wxListEvent& e)
{
	this->PopupMenu(m_pMenu);
}

void FoodList::OnOpenItem(wxCommandEvent& event)
{

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

