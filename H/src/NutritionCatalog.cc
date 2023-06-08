#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/valgen.h>

#include "Font/Font.hpp"
#include "NutritionCatalog.h"
#include "StandardPath.hpp"

#include "Nutrient Total/Total.hpp"

// =================== ItemViewer ===================

class ItemViewer : public wxDialog
{
private:
	// Item stuff
	CatalogItem m_catalogItem;
	wxString m_itemName;
	wxStaticBitmap* m_itemBmp;

	CalorieList* m_pCalorieList;

	// Dialog stuff
	wxButton* m_pAdd; // adding the food item to the nutrition log
	wxButton* m_pClose;
	
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pButtonSizer;
	wxBoxSizer* m_pTextInfoSizer;
	wxBoxSizer* m_pContentSizer;
	wxFlexGridSizer* m_pQuantitySizer;

	wxStaticText* m_pNutrFactsTxt;
	wxStaticText* m_pCalTxt;
	wxStaticText* m_pProteinTxt;
	wxStaticText* m_pCarbTxt;

	wxSpinCtrl* m_pQuantity;
	int m_quantity;

public:
	const int GetQuantity() const { return m_quantity; }
	void SetCalorieList(CalorieList* pCalorieList) { m_pCalorieList = pCalorieList; }

public:
	ItemViewer(CalorieList* pCalorieList,
		CatalogItem catalogItem,
		wxWindow* parent,
		wxWindowID id = -1,
		const wxString& title = _T("View Nutrition Item"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX)
		: wxDialog(parent, id, title, pos, size, style), m_catalogItem{ catalogItem }, m_pCalorieList{ pCalorieList }
	{
		// Set the title to include the item which is being viewed
		this->SetTitle(wxString(_T("Nutritional Item - ")) << m_catalogItem.GetName());

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

		m_pQuantity = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 1, 100, 1);
		m_pQuantity->SetValidator(wxGenericValidator(&m_quantity));
	}

	void SetupSizers()
	{
		m_pTopSizer = new wxBoxSizer(wxVERTICAL);
		m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
		m_pTextInfoSizer = new wxBoxSizer(wxVERTICAL);
		m_pContentSizer = new wxBoxSizer(wxHORIZONTAL);
		m_pQuantitySizer = new wxFlexGridSizer(2, wxSize(5, 1));
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

		// Quantity sizer
		m_pQuantitySizer->Add(new wxStaticText(this, wxID_STATIC, _T("Quantity:")), wxSizerFlags().Left().Border(wxALL, 5));
		m_pQuantitySizer->Add(m_pQuantity, wxSizerFlags().Left().Border(wxALL, 5));

		// Top sizer
		m_pTopSizer->Add(m_pContentSizer);
		m_pTopSizer->Add(m_pQuantitySizer);
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
		if (Validate() && TransferDataFromWindow())
		{
			SetReturnCode(wxID_CLOSE);
			Show(false);
		}
	}

	void OnAddToNutritionLog(wxCommandEvent& event)
	{
		if (Validate() && TransferDataFromWindow())
		{
			NutrientContent nc{ m_catalogItem.GetCalories() * m_quantity, m_catalogItem.GetProtein() * m_quantity, m_catalogItem.GetCarbohydrates() * m_quantity, m_catalogItem.GetFiber() * m_quantity };
#ifdef _DEBUG
			if (m_pCalorieList == nullptr)
				wxMessageBox(_T("Calorie List is null."));
#endif
			if (m_pCalorieList)
				m_pCalorieList->AddItem(m_catalogItem.GetName(), nc);
		}
	}
};

// =================== FoodList ===================

FoodList::FoodList(CalorieList* pCalorieList, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxListView(parent, id, pos, size, style), m_pCalorieList{ pCalorieList }
{
	m_pFrame = reinterpret_cast<wxFrame*>(parent);

	this->Init();

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
	this->SetupDefaultNutritionItems();
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

void FoodList::SetupDefaultNutritionItems()
{
	wxBitmap eggBmp = wxBitmap(path_data::dataDir + _T("\\Images\\nutrition\\eggs.png"), wxBITMAP_TYPE_PNG);
	wxBitmap appleBmp = wxBitmap(path_data::dataDir + _T("\\Images\\nutrition\\apple.png"), wxBITMAP_TYPE_PNG);

	// Define catalog items
	CatalogItem eggs(_T("Eggs"), eggBmp, 60, 6, 0, 0);
	CatalogItem red_apple(_T("Red Apple (medium)"), appleBmp, 95, 1, 25, 4);
	CatalogItem bacon(_T("Bacon (100g)"), wxNullBitmap, 541, 37, 1, 0);

	// Add items to the nutrition list
	this->AddNutritionItem(eggs);
	this->AddNutritionItem(red_apple);
	this->AddNutritionItem(bacon);
}

void FoodList::AddNutritionItem(const CatalogItem& info)
{
	m_catalogItems.push_back(info);

	wxString name = info.GetName();
	wxBitmap bmp = info.GetBmp();
	
	if (info.GetBmp().IsOk())
	{
		m_pImageList->Add(bmp);
		this->InsertItem(m_insertionIndex, name, m_bmpIndex);
	}
	else
	{
		this->InsertItem(m_insertionIndex, name, -1);
	}

	++m_insertionIndex;
	++m_bmpIndex;
}

void FoodList::OpenItem()
{
	m_pItemViewer = new ItemViewer(m_pCalorieList, m_catalogItems[m_selectionIndex], this);
	m_pItemViewer->Show(true);
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

NutritionCatalog::NutritionCatalog(CalorieList* pCalorieList, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style), m_pCalorieList{ pCalorieList }
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
	m_pFoodList = new FoodList(m_pCalorieList, this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
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

