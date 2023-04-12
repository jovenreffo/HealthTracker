#include <wx/statline.h>
#include <wx/stattext.h>

#include "Font/Font.hpp"
#include "NutritionCatalog.h"
#include "StandardPath.hpp"

// =================== ItemViewer ===================

class ItemViewer : public wxDialog
{
private:
	// Item stuff
	CatalogItem m_catalogItem;
	wxString m_itemName;
	wxStaticBitmap* m_itemBmp;

	// Dialog stuff
	wxButton* m_pAdd; // adding the food item to the nutrition log
	wxButton* m_pClose;
	
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxBoxSizer* m_pTextInfoSizer;
	wxBoxSizer* m_pContentSizer;

	wxStaticText* m_pNutrFactsTxt;
	wxStaticText* m_pCalTxt;
	wxStaticText* m_pProteinTxt;
	wxStaticText* m_pCarbTxt;

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
		m_pAdd->Bind(wxEVT_BUTTON, &ItemViewer::OnAddToNutritionLog, this);
		m_pClose->Bind(wxEVT_BUTTON, &ItemViewer::OnClose, this);
	}

	~ItemViewer() 
	{
		// Unbind events
		m_pAdd->Unbind(wxEVT_BUTTON, &ItemViewer::OnAddToNutritionLog, this);
		m_pClose->Unbind(wxEVT_BUTTON, &ItemViewer::OnClose, this);
	}

	void Init()
	{
		// Set variable information
		m_itemName = m_catalogItem.GetName();
		m_itemBmp = new wxStaticBitmap(this, wxID_ANY, m_catalogItem.GetBmp(), wxDefaultPosition, wxDefaultSize);

		this->SetupControls();
		this->SetupSizers();
		this->SetupWindow();
	}

	void SetupControls()
	{
		// Buttons
		m_pAdd = new wxButton(this, wxID_ADD, _T("Add to Nutrition Log"), wxDefaultPosition, wxDefaultSize);
		m_pClose = new wxButton(this, wxID_CLOSE, _T("Close"), wxDefaultPosition, wxDefaultSize);

		// Text
		m_pNutrFactsTxt = new wxStaticText(this, wxID_STATIC, _T("Nutrition Information"), wxDefaultPosition, wxDefaultSize);
		m_pNutrFactsTxt->SetFont(Fonts::GetBoldFont(11));

		m_pCalTxt = new wxStaticText(this, wxID_STATIC, wxString(_T("Calories: ")) << m_catalogItem.GetCalories());
		m_pProteinTxt = new wxStaticText(this, wxID_STATIC, wxString(_T("Protein: ")) << m_catalogItem.GetProtein() << 'g');
		m_pCarbTxt = new wxStaticText(this, wxID_STATIC, wxString(_T("Carbohydrates: ")) << m_catalogItem.GetCarbohydrates() << 'g');
	}

	void SetupSizers()
	{
		m_pTopSizer = new wxBoxSizer(wxVERTICAL);
		m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
		m_pTextInfoSizer = new wxBoxSizer(wxVERTICAL);
		m_pContentSizer = new wxBoxSizer(wxHORIZONTAL);
		this->SetSizerAndFit(m_pTopSizer);

		// Button sizer
		m_pButtonSizer->Add(m_pAdd, wxSizerFlags().CentreVertical().Border(wxALL, 5));
		m_pButtonSizer->Add(m_pClose, wxSizerFlags().CentreVertical().Border(wxALL, 5));

		// Text info sizer
		m_pTextInfoSizer->Add(m_pNutrFactsTxt, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
		m_pTextInfoSizer->Add(m_pCalTxt, wxSizerFlags().Left().Border(wxALL, 5));
		m_pTextInfoSizer->Add(m_pProteinTxt, wxSizerFlags().Left().Border(wxALL, 5));
		m_pTextInfoSizer->Add(m_pCarbTxt, wxSizerFlags().Left().Border(wxALL, 5));

		// Content sizer
		m_pContentSizer->Add(m_itemBmp, wxSizerFlags().Left().Border(wxALL, 5));
		m_pContentSizer->Add(m_pTextInfoSizer);

		// Top sizer
		m_pTopSizer->Add(m_pContentSizer);
		m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));
		m_pTopSizer->Add(m_pButtonSizer);
	}

	void SetupWindow()
	{
		// Sizing
		wxSize sz = this->DoGetBestSize();

		this->SetInitialSize(sz);
		this->SetMinSize(sz);
		this->SetMaxSize( wxSize(sz.x + 200, sz.y + 150) );

		// Positioning
		this->Centre();
	}

	// Events
	void OnClose(wxCommandEvent& event)
	{
		SetReturnCode(wxID_CLOSE);
		Show(false);
	}

	void OnAddToNutritionLog(wxCommandEvent& event)
	{

	}
};

// =================== FoodList ===================

FoodList::FoodList(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style)
{
	m_pFrame = reinterpret_cast<wxFrame*>(parent);

	this->Init();

	wxBitmap egg = wxBitmap(path_data::dataDir + _T("\\Images\\nutrition\\eggs.png"), wxBITMAP_TYPE_PNG);
	CatalogItem ci("Eggs", egg, 60, 6, 0);
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

#ifdef wxUSE_STATUSBAR
	if (IsSelected(m_selectionIndex))
		m_pFrame->SetStatusText(wxString(_T("Current item: ")) << m_currentItemName);
	else
		m_pFrame->SetStatusText(_T("No item selected."));
#endif
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

	this->Centre();
}

