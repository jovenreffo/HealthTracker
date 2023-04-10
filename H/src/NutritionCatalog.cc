#include <wx/statline.h>
#include "NutritionCatalog.h"
#include "StandardPath.hpp"

// =================== ItemViewer ===================

class ItemViewer : public wxDialog
{
private:
	// Item stuff
	CatalogItem m_catalogItem;
	wxString m_itemName;
	wxBitmap m_itemBmp;

	// Dialog stuff
	wxButton* m_pAdd; // adding the food item to the nutrition log
	wxButton* m_pClose;
	
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;

public:
	ItemViewer(CatalogItem catalogItem,
		wxWindow* parent,
		wxWindowID id = -1,
		const wxString& title = _T("View Nutrition Item"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX)
		: wxDialog(parent, id, title, pos, size, style), m_catalogItem{ catalogItem }
	{
		// Set the title to include the item which is being viewed
		this->SetTitle(wxString(_T("View Nutritional Item - ")) << m_catalogItem.GetName());

		this->Init();

		// Bind events
	}

	~ItemViewer() {}

	void Init()
	{
		// Set variable information
		m_itemName = m_catalogItem.GetName();
		m_itemBmp = m_catalogItem.GetBmp();

		this->SetupControls();
		this->SetupSizers();
		this->SetupSizing();
	}

	void SetupControls()
	{
		// Buttons
		m_pAdd = new wxButton(this, wxID_ADD, _T("Add to Nutrition Log"), wxDefaultPosition, wxDefaultSize);
		m_pClose = new wxButton(this, wxID_CLOSE, _T("Close"), wxDefaultPosition, wxDefaultSize);
	}

	void SetupSizers()
	{
		m_pTopSizer = new wxBoxSizer(wxVERTICAL);
		m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
		this->SetSizerAndFit(m_pTopSizer);

		m_pButtonSizer->Add(m_pAdd, wxSizerFlags().CentreVertical().Border(wxALL, 5));
		m_pButtonSizer->Add(m_pClose, wxSizerFlags().CentreVertical().Border(wxALL, 5));

		m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
		m_pTopSizer->Add(m_pButtonSizer);
	}

	void SetupSizing()
	{
		wxSize sz = this->DoGetBestSize();

		this->SetInitialSize(sz);
		this->SetMinSize(sz);
		this->SetMaxSize( wxSize(sz.x + 200, sz.y + 150) );
	}

	// Events
	void OnClose(wxCommandEvent& event)
	{

	}

	void OnAddToNutritionLog(wxCommandEvent& event)
	{

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
	this->Bind(wxEVT_LIST_ITEM_SELECTED, &FoodList::OnSelectItem, this);
	this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &FoodList::OnRightClickItem, this);
	this->Bind(wxEVT_LIST_ITEM_ACTIVATED, &FoodList::OnDoubleClickItem, this);

	m_pMenu->Bind(wxEVT_MENU, &FoodList::OnOpenItem, this, wxID_OPEN);
}

FoodList::~FoodList()
{
	// Unbind events
	this->Unbind(wxEVT_LIST_ITEM_SELECTED, &FoodList::OnSelectItem, this);
	this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &FoodList::OnRightClickItem, this);
	this->Unbind(wxEVT_LIST_ITEM_ACTIVATED, &FoodList::OnDoubleClickItem, this);

	m_pMenu->Unbind(wxEVT_MENU, &FoodList::OnOpenItem, this, wxID_OPEN);
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
	m_catalogItems.push_back(info);

	wxString name = info.GetName();
	wxBitmap bmp = info.GetBmp();

	m_pImageList->Add(bmp);
	this->InsertItem(0, name);
	this->SetItemImage(0, 0);
}

void FoodList::OpenItem()
{
	m_pItemViewer = new ItemViewer(m_catalogItems[0], this);
	m_pItemViewer->Show(true);

	if (m_pItemViewer->ShowModal() == wxID_OK)
	{

	}
}

void FoodList::OnSelectItem(wxListEvent& event)
{
	m_selectionIndex = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	m_currentItemName = GetItemText(m_selectionIndex, 0);
}

void FoodList::OnDoubleClickItem(wxListEvent& e)
{
	this->OpenItem();
}

void FoodList::OnRightClickItem(wxListEvent& e)
{
	this->PopupMenu(m_pMenu);
}

void FoodList::OnOpenItem(wxCommandEvent& event)
{
	this->OpenItem();
}

// =================== NutritionCatalog ===================

NutritionCatalog::NutritionCatalog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	this->SetBackgroundColour(wxColour(240, 240, 240));
	this->SetIcon(wxIcon(path_data::dataDir + _T("\\Images\\catalog.png"), wxBITMAP_TYPE_PNG));

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

