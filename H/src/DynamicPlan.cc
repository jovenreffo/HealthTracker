#include <wx/valgen.h>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/listctrl.h>
#include "DynamicPlan.h"
#include "StandardPath.hpp"

class CounterList : public wxListView
{
private:
	long m_total;
	wxMenu* m_pMenu;

public:
	CounterList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT)
		: wxListView(parent, id, pos, size, style)
	{
		this->Init();
		
		// Bind events
		this->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &CounterList::OnRightClick, this);
		m_pMenu->Bind(wxEVT_MENU, &CounterList::OnDeleteItem, this, wxID_DELETE);
	}

	~CounterList()
	{
		// Unbind events
		this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &CounterList::OnRightClick, this);
		m_pMenu->Bind(wxEVT_MENU, &CounterList::OnDeleteItem, this, wxID_DELETE);
	}

	void Init()
	{
		this->InsertColumn(0, _T("Repetitions"), 0, 100);
		this->SetupMenu();
		this->SetupTotalItem();
	}

	void SetupMenu()
	{
		m_pMenu = new wxMenu();
		m_pMenu->Append(wxID_DELETE, _T("Delete"));
	}

	void SetupTotalItem()
	{
		this->InsertItem(0, _T("Total"));
	}

	void AddReps(int count)
	{
		/*
		* Similar to CalorieList, a total item has been created at index 0.
		* In order to have the total "pinned" at the top, items will be inserted at index 1 in the list.
		* The rep spin ctrl also has an int validator, so it must be converted to a string.
		*/
		if (!count)
		{
			wxMessageBox(_T("Please enter a value."), _T("Invalid Value"), wxOK | wxICON_EXCLAMATION);
			return;
		}

		this->InsertItem(1, std::to_string(count));
		this->UpdateTotal();
	}

	void UpdateTotal()
	{
		/*
		* Also similar to the CalorieList class, begin index 1 in calculating the total, because we do not want to include the total itself.
		* Here, also start by resetting the current contents of the total.
		* Lastly, call SetItem(index, col, str) at index 0 col 0 to update the total
		*/
		m_total = 0L;

		for (auto i{ 1 }; i < this->GetItemCount(); ++i)
		{
			m_total += wxAtoi(this->GetItemText(i, 0));
		}

		this->SetItem(0, 0, wxString(_T("Total: ")) << std::to_string(m_total));
	}

	long GetTotal() const { return m_total; }

	// events
	void OnRightClick(wxListEvent& event)
	{
		this->PopupMenu(m_pMenu);
	}

	void OnDeleteItem(wxCommandEvent& event)
	{
		int selected = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

		// Here, a confirmation box is not necessary as there will most likely be many items in the list
		if (selected > 0)
		{
			this->DeleteItem(selected);
			this->UpdateTotal();
		}
	}
};

CustomExercisePanel::CustomExercisePanel(const wxString& exerciseName, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style), m_exerciseName{ exerciseName }
{
	this->Init();

	// Event binding
	m_pAddButton->Bind(wxEVT_BUTTON, &CustomExercisePanel::OnAddReps, this);
	m_pSpinCtrl->Bind(wxEVT_TEXT_ENTER, &CustomExercisePanel::OnEnter, this);
}

CustomExercisePanel::~CustomExercisePanel()
{
	// Unbind events
	m_pAddButton->Unbind(wxEVT_BUTTON, &CustomExercisePanel::OnAddReps, this);
	m_pSpinCtrl->Unbind(wxEVT_TEXT_ENTER, &CustomExercisePanel::OnEnter, this);
}

void CustomExercisePanel::Init()
{
	this->SetupSizers();
}

void CustomExercisePanel::SetupControls()
{
	m_pSpinCtrl = new wxSpinCtrl(this, static_cast<int>(CEP::ID_REPS_SPINCTRL), _T("0"),
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 0, 1000, 0, _T("RepetitionSpinCtrl"));
	m_pSpinCtrl->SetValidator(wxGenericValidator(&m_repCount));

	m_pAddButton = new wxBitmapButton(this, static_cast<int>(CEP::ID_ADD_REPS), wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG),
		wxDefaultPosition, wxDefaultSize);

	m_pCounterList = new CounterList(this, static_cast<int>(CEP::ID_REP_COUNTER), wxDefaultPosition, wxDefaultSize);
	m_pCounterList->Show(true);
}

void CustomExercisePanel::SetupSizers()
{
	m_pControlSizer = new wxFlexGridSizer(3, wxSize(5, 1));
	m_pTopSizer = new wxStaticBoxSizer(wxVERTICAL, this, m_exerciseName);
	m_pTopParent = m_pTopSizer->GetStaticBox();
	this->SetSizerAndFit(m_pTopSizer);

	// Set up the controls with m_pTopParent as the parent window
	this->SetupControls();

	// Arrange the controls on the sizers
	m_pTopSizer->Add(m_pCounterList, wxSizerFlags().Proportion(1).Expand().Left().Border(wxALL, 5));

	// Control sizer
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Reps:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pControlSizer->Add(m_pSpinCtrl, wxSizerFlags().Left().Border(wxALL, 5).Proportion(1));
	m_pControlSizer->Add(m_pAddButton, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopSizer->Add(m_pControlSizer, wxSizerFlags().Left().Border(wxALL, 5));
}

// events

void CustomExercisePanel::OnAddReps(wxCommandEvent& event)
{
	m_pCounterList->AddReps(m_pSpinCtrl->GetValue());
}

void CustomExercisePanel::OnEnter(wxCommandEvent& event)
{
	m_pCounterList->AddReps(m_pSpinCtrl->GetValue());
}

// DynamicPlan

DynamicPlan::DynamicPlan(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxScrolled<wxPanel>(parent, id, pos, size, style, _T("DynamicPlanWin"))
{
	this->SetScrollRate(10, 10);
	this->Init();

#ifdef _DEBUG
	m_pCustomExercisePanel = new CustomExercisePanel(_T("Pullups"), this, wxID_ANY);
	m_pCustomExercisePanel->Show(true);

	wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(pTopSizer);
	pTopSizer->Add(m_pCustomExercisePanel, wxSizerFlags().Expand().Proportion(1).Border(wxALL, 10));
#endif
}

void DynamicPlan::Init()
{

}