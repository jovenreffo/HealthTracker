#include <wx/valgen.h>
#include <wx/valtext.h>
#include <wx/msgdlg.h>
#include <wx/statline.h>
#include <wx/listctrl.h>
#include <wx/filedlg.h>
#include <wx/file.h>
#include <wx/string.h>
#include <wx/config.h>
#include <wx/datetime.h>

#include "DynamicPlan.h"
#include "StandardPath.hpp"

class CounterList : public wxListView
{
private:
	long m_total;
	wxMenu* m_pMenu;
	wxMenu* m_pMenuCol;

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
		this->Bind(wxEVT_LIST_COL_RIGHT_CLICK, &CounterList::OnRightClickColumn, this);
		this->Bind(wxEVT_KEY_DOWN, &CounterList::OnKey, this);
		m_pMenu->Bind(wxEVT_MENU, &CounterList::OnDeleteItem, this, wxID_DELETE);
		m_pMenuCol->Bind(wxEVT_MENU, &CounterList::OnClearList, this, wxID_CLEAR);
	}

	~CounterList()
	{
		// Unbind events
		this->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &CounterList::OnRightClick, this);
		this->Unbind(wxEVT_LIST_COL_RIGHT_CLICK, &CounterList::OnRightClickColumn, this);
		this->Unbind(wxEVT_KEY_DOWN, &CounterList::OnKey, this);
		m_pMenu->Unbind(wxEVT_MENU, &CounterList::OnDeleteItem, this, wxID_DELETE);
		m_pMenuCol->Unbind(wxEVT_MENU, &CounterList::OnClearList, this, wxID_CLEAR);
	}

	void Init()
	{
		this->InsertColumn(0, _T("Repetitions"), 0, 100);
		this->SetupMenu();
	}

	void SetupMenu()
	{
		// Menu on right click item
		m_pMenu = new wxMenu();
		m_pMenu->Append(wxID_DELETE, _T("&Delete"));

		// Right-clicking columns
		m_pMenuCol = new wxMenu();
		m_pMenuCol->Append(wxID_CLEAR, _T("&Clear"));
	}

	void AddReps(int count)
	{
		/*
		* The rep spin ctrl has an int validator, so it must be converted to a string.
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
		* Start by resetting the current contents of the total.
		* Lastly, call SetItem(index, col, str) at index 0 col 0 to update the total
		*/
		m_total = 0L;

		for (auto i{ 0 }; i < this->GetItemCount(); ++i)
		{
			m_total += wxAtoi(this->GetItemText(i, 0));
		}

		wxListItem item;
		item.SetText(wxString(_T("Repetitions: ")) << m_total);
		this->SetColumn(0, item);
	}

	void HandleDeleteItem()
	{
		int selected = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

		this->DeleteItem(selected);
		this->UpdateTotal();
	}

	long GetTotal() const { return m_total; }

	// events
	void OnRightClick(wxListEvent& event)
	{
		this->PopupMenu(m_pMenu);
	}

	void OnRightClickColumn(wxListEvent& event)
	{
		this->PopupMenu(m_pMenuCol);
	}

	void OnDeleteItem(wxCommandEvent& event)
	{
		this->HandleDeleteItem();
	}

	void OnClearList(wxCommandEvent& event)
	{
		this->DeleteAllItems();
		this->UpdateTotal();
	}

	void OnKey(wxKeyEvent& event)
	{
		switch (event.GetUnicodeKey())
		{
		case WXK_DELETE:
			this->HandleDeleteItem();
			break;
		}

		event.Skip();
	}
};

CustomExercisePanel::CustomExercisePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();

	// Event binding
	m_pAddButton->Bind(wxEVT_BUTTON, &CustomExercisePanel::OnAddReps, this);
	m_pSaveButton->Bind(wxEVT_BUTTON, &CustomExercisePanel::OnSave, this);
	m_pSpinCtrl->Bind(wxEVT_TEXT_ENTER, &CustomExercisePanel::OnEnter, this);
}

CustomExercisePanel::~CustomExercisePanel()
{
	// Unbind events
	m_pAddButton->Unbind(wxEVT_BUTTON, &CustomExercisePanel::OnAddReps, this);
	m_pSaveButton->Unbind(wxEVT_BUTTON, &CustomExercisePanel::OnSave, this);
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

	m_pAddButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG),
		wxDefaultPosition, wxDefaultSize);

	m_pSaveButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(path_data::dataDir + _T("\\Images\\save.png"), wxBITMAP_TYPE_PNG), wxDefaultPosition, wxDefaultSize);

	m_pCounterList = new CounterList(this, static_cast<int>(CEP::ID_REP_COUNTER), wxDefaultPosition, wxDefaultSize);
	m_pCounterList->Show(true);
}

void CustomExercisePanel::SetupSizers()
{
	m_pControlSizer = new wxFlexGridSizer(4, wxSize(5, 1));
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
	m_pControlSizer->Add(m_pSaveButton, wxSizerFlags().Left().Border(wxALL, 5));
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

void CustomExercisePanel::OnSave(wxCommandEvent& event)
{
	// TODO: change the default file name
	wxFileDialog* pSaveDialog = new wxFileDialog(this, _T("Save Exercise Information"), wxEmptyString, wxEmptyString, _T("Text files (*.txt)|*.txt"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	wxString fileName, filePath;
	wxFile textFile;

	if (pSaveDialog->ShowModal() == wxID_OK)
	{
		fileName = pSaveDialog->GetFilename();
		filePath = pSaveDialog->GetPath();
		textFile.Create(filePath);
	}
	else return;

	if (!textFile.Exists(filePath))
	{
		wxLogError(_T("Failed to create text file: %s"), fileName);
		return;
	}

	if (textFile.Open(filePath, wxFile::write))
	{
		textFile.Write(wxString(_T("Repetitions: ")) << m_pSpinCtrl->GetValue());

		// the user has checked the option of including the date / time in the text file
		if (wxConfigBase::Get()->Read("/Preferences/IncludeDTReps", 0L))
		{
			wxDateTime dt;
			dt.SetToCurrent();
			textFile.Write(wxString(_T("\nThis text file was generated: ")) << dt.FormatDate());
		}
	}

	// clean up
	textFile.Close();
	pSaveDialog->Destroy();
}

// AddExerciseDialog

AddExerciseDialog::AddExerciseDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
}

void AddExerciseDialog::Init()
{
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void AddExerciseDialog::CustomRefresh()
{
	this->SetSize(wxSize(this->GetSize().GetWidth() + 1, this->GetSize().GetHeight() + 1));
	this->SetSize(wxSize(this->GetSize().GetWidth() - 1, this->GetSize().GetHeight() - 1));
}

void AddExerciseDialog::SetupSizing()
{
	this->SetInitialSize(AED_SIZE);
	this->SetMinSize(AED_SIZE);
	//this->SetMaxSize(AED_SIZE_MAX);
}

void AddExerciseDialog::SetupControls()
{
	m_pExerciseNameTxt = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxTextValidator(0, &m_exerciseName));
	m_pExerciseNameTxt->Bind(wxEVT_TEXT_ENTER, &AddExerciseDialog::OnEnter, this);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
	m_pSearchImg = new wxButton(this, wxID_ANY, _T("Search"), wxDefaultPosition, wxDefaultSize);
	m_pSearchImg->SetToolTip(_T("Set a custom image for this exercise. 16x16 for best results."));

	m_pImageLabel = new wxStaticText(this, wxID_ANY, _T("Image: No selection."), wxDefaultPosition, wxDefaultSize);

	// bind
	m_pSearchImg->Bind(wxEVT_BUTTON, &AddExerciseDialog::OnSearch, this);
}

void AddExerciseDialog::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pHorizontalSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pButtonSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	this->SetSizerAndFit(m_pTopSizer);

	// Main controls
	m_pHorizontalSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Exercise name:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pExerciseNameTxt, wxSizerFlags().Left().Border(wxALL, 5));
	m_pHorizontalSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Custom icon (16x16):")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pSearchImg, wxSizerFlags().Left().Border(wxALL, 5));
	m_pHorizontalSizer->Add(m_pImageLabel, wxSizerFlags().Left().Border(wxALL, 5));
	m_pHorizontalSizer->AddSpacer(0);
	m_pTopSizer->Add(m_pHorizontalSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));

	// separator
	m_pTopSizer->Add(new wxStaticLine(this, wxID_STATIC), wxSizerFlags().Expand().Border(wxALL, 5));

	// Button sizer
	m_pButtonSizer->Add(m_pOk, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().CentreVertical().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer, wxSizerFlags().CentreHorizontal().Border(wxALL, 5));
}

// events

void AddExerciseDialog::OnOK(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void AddExerciseDialog::OnCancel(wxCommandEvent& event)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

void AddExerciseDialog::OnClose(wxCloseEvent& event)
{
	this->SetReturnCode(wxID_CLOSE);
	this->Show(false);
}

void AddExerciseDialog::OnEnter(wxCommandEvent& event)
{
	if (Validate() && TransferDataFromWindow())
	{
		this->SetReturnCode(wxID_OK);
		this->Show(false);
	}
}

void AddExerciseDialog::OnSearch(wxCommandEvent& event)
{
	wxFileDialog* pOpenDialog = new wxFileDialog(this, _T("Open Image File"), wxEmptyString, wxEmptyString, _T("PNG files (*.png)|*.png|ICO files (*.ico)|*.ico|BMP files (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	wxInitAllImageHandlers();

	if (pOpenDialog->ShowModal() == wxID_OK)
	{
		m_imagePath = pOpenDialog->GetPath();

		// The filter index tells us which file type the user chose.
		switch (pOpenDialog->GetFilterIndex())
		{
		case 0: // png
			m_image = wxBitmap(m_imagePath, wxBITMAP_TYPE_PNG);
			m_bitmapType = wxBITMAP_TYPE_PNG;
			break;
		case 1: // ico
			m_image = wxBitmap(m_imagePath, wxBITMAP_TYPE_ICO);
			m_bitmapType = wxBITMAP_TYPE_ICO;
			break;
		case 2: // bmp
			m_image = wxBitmap(m_imagePath, wxBITMAP_TYPE_BMP);
			m_bitmapType = wxBITMAP_TYPE_BMP;
			break;
		default:
			wxLogError(_T("Unrecognized file type. Please try again."));
			break;
		}

		m_bUseImage = true;
	}

	// check to make sure the image is ok and the file path is not empty before issuing an error
	if (!m_image.IsOk() && !m_imagePath.empty())
	{
		wxLogError(_T("Failed to load image: %s"), m_imagePath);
	}

	// Update the file name and display it on the dialog
	m_pImageLabel->SetLabel(wxString(_T("Image: ")) << pOpenDialog->GetFilename());
	m_pImageLabel->Show(true);
}

// DynamicPlan

DynamicPlan::DynamicPlan(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxScrolled<wxPanel>(parent, id, pos, size, style, _T("DynamicPlanWin"))
{
	this->SetScrollRate(10, 10);
	this->Init();

	// Bind events
	m_pAddExercise->Bind(wxEVT_BUTTON, &DynamicPlan::OnAddExercise, this);
	m_pOpenSpreadSheet->Bind(wxEVT_BUTTON, &DynamicPlan::OnOpenSpreadsheet, this);
}

DynamicPlan::~DynamicPlan()
{
	// Unbind events
	m_pAddExercise->Unbind(wxEVT_BUTTON, &DynamicPlan::OnAddExercise, this);
	m_pOpenSpreadSheet->Unbind(wxEVT_BUTTON, &DynamicPlan::OnOpenSpreadsheet, this);
}

void DynamicPlan::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void DynamicPlan::SetupControls()
{
	// Top-level buttons
	m_addBmp = wxBitmap(path_data::dataDir + _T("\\Images\\add.png"), wxBITMAP_TYPE_PNG);
	m_spreadsheetBmp = wxBitmap(path_data::dataDir + _T("\\Images\\spreadsheet.png"), wxBITMAP_TYPE_PNG);

	m_pAddExercise = new wxButton(this, wxID_ANY, _T("Add Exercise"), wxDefaultPosition, wxDefaultSize);
	m_pOpenSpreadSheet = new wxButton(this, wxID_ANY, _T("Open Spreadsheet"), wxDefaultPosition, wxDefaultSize);
	m_pAddExercise->SetBitmap(m_addBmp);
	m_pOpenSpreadSheet->SetBitmap(m_spreadsheetBmp);

	m_pHtmlPanelCover = new HtmlPanelCover(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pHtmlPanelCover->Show(true);

	// ExerciseNotebook
	m_pExerciseNotebook = new ExerciseNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pExerciseNotebook->Show(false);
}

void DynamicPlan::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pTopButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pTopButtonSizer->Add(m_pAddExercise, wxSizerFlags().Left().Border(wxALL, 5));
	m_pTopButtonSizer->Add(m_pOpenSpreadSheet, wxSizerFlags().Left().Border(wxALL, 5));

	m_pTopSizer->Add(m_pTopButtonSizer);
	m_pTopSizer->Add(m_pHtmlPanelCover, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pExerciseNotebook, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));
}

void DynamicPlan::CustomRefresh()
{
	// CustomRefresh:
	// Simply increase the size and then decrement by 1 to return to original state.
	// If this breaks in the future, resort to wxUpdateUIEvent
	this->SetSize(wxSize(this->GetSize().GetWidth() + 1, this->GetSize().GetHeight() + 1));
	this->SetSize(wxSize(this->GetSize().GetWidth() - 1, this->GetSize().GetHeight() - 1));
}

// events

void DynamicPlan::OnAddExercise(wxCommandEvent& event)
{
	m_pAddExerciseDialog = new AddExerciseDialog(this, wxID_ANY);
	m_pAddExerciseDialog->Show(true);

	if (m_pAddExerciseDialog->ShowModal() == wxID_OK)
	{
		// The cover should only be shown at the start of the program, when the user has not added any exercises to the notbook
		// If the cover is shown, set m_bShowCover to false, hide the cover, and show the notebook. Finally, refresh the panel.
		if (m_bShowCover) 
		{
			m_bShowCover = false;
			m_pHtmlPanelCover->Show(false);
			m_pExerciseNotebook->Show(true);
			this->CustomRefresh();
		}

		// Add an image to the notebook's image list and create a new exercise page
		
		m_pExerciseNotebook->AddImageToList(m_pAddExerciseDialog->GetImage());
		m_pExerciseNotebook->AddExercisePage(new CustomExercisePanel(this, wxID_ANY), m_pAddExerciseDialog->GetExerciseName(), m_pAddExerciseDialog->UseImage());
	}
}

void DynamicPlan::OnOpenSpreadsheet(wxCommandEvent& event)
{
	m_pSpreadsheetWindow = new SpreadsheetWindow(this, wxID_ANY, _T("Spreadsheet"), wxDefaultPosition);
	m_pSpreadsheetWindow->Show(true);
}

// ExerciseNotebook

ExerciseNotebook::ExerciseNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxAuiNotebook(parent, id, pos, size, style)
{
	this->Init();

	// Connect events
	this->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &ExerciseNotebook::OnCloseTab, this);
	this->Bind(wxEVT_AUINOTEBOOK_TAB_RIGHT_DOWN, &ExerciseNotebook::OnRightClickTab, this);
	
	// bind close event to the pop-up menu as well
	m_pTabMenu->Bind(wxEVT_MENU, &ExerciseNotebook::OnCloseTabMenu, this, wxID_CLOSE);
}

ExerciseNotebook::~ExerciseNotebook()
{
	this->Unbind(wxEVT_AUINOTEBOOK_PAGE_CLOSED, &ExerciseNotebook::OnCloseTab, this);
	this->Unbind(wxEVT_AUINOTEBOOK_TAB_RIGHT_DOWN, &ExerciseNotebook::OnRightClickTab, this);
}

void ExerciseNotebook::Init()
{
	this->SetupMenu();
	this->SetupImageList();
}

void ExerciseNotebook::SetupMenu()
{
	m_pTabMenu = new wxMenu();

	m_pTabMenu->Append(wxID_CLOSE, _T("Close Tab"));
}

void ExerciseNotebook::SetupImageList()
{
	// prepare the image list for use
	m_pImageList = new wxImageList(16, 16);

	this->AssignImageList(m_pImageList);
}

void ExerciseNotebook::AddExercisePage(CustomExercisePanel* pExercisePanel, const wxString& title, bool bUseImage)
{	
	// If the user has selected an image to be used, initialize a new page with the image index
	if (bUseImage)
		this->AddPage(pExercisePanel, title, true, m_currentImageIndex);
	else // Otherwise leave it blank
		this->AddPage(pExercisePanel, title, true, -1);
}

void ExerciseNotebook::AddImageToList(const wxBitmap& bmp)
{
	if (bmp.IsOk() && m_pImageList != nullptr)
	{
		m_pImageList->Add(bmp);
		++m_currentImageIndex;
	}
}

// events for ExerciseNotebook

void ExerciseNotebook::OnCloseTabMenu(wxCommandEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to close this tab and lose all of its data?"), _T("Confirm"), wxYES_NO) == wxYES)
	{
		if (m_selectionIndex != -1)
			this->DeletePage(m_selectionIndex);
	}
}

void ExerciseNotebook::OnCloseTab(wxAuiNotebookEvent& event)
{
	if (wxMessageBox(_T("Are you sure you want to close this tab and lose all of its data?"), _T("Confirm"), wxYES_NO) == wxNO)
		event.Veto();
}

void ExerciseNotebook::OnRightClickTab(wxAuiNotebookEvent& event)
{
	this->PopupMenu(m_pTabMenu);
}

void ExerciseNotebook::OnPageChange(wxAuiNotebookEvent& event)
{
	m_selectionIndex = this->GetSelection();
}

// HtmlPanelCover

HtmlPanelCover::HtmlPanelCover(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);

	wxHtmlWindow* pHtmlWin = new wxHtmlWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_DEFAULT_STYLE);
	pHtmlWin->SetBorders(0);
	pHtmlWin->LoadPage(path_data::dataDir + _T("\\H\\src\\HTML\\dynamic_plan_cover.html"));
	pHtmlWin->SetInitialSize(wxSize(pHtmlWin->GetInternalRepresentation()->GetWidth(), pHtmlWin->GetInternalRepresentation()->GetHeight()));

	pTopSizer->Add(pHtmlWin, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 5));

	this->SetSizer(pTopSizer);
	pTopSizer->Fit(this);
}