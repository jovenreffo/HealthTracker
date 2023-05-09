#ifndef DYNAMICPLAN_H
#define DYNAMICPLAN_H

#include <wx/panel.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/scrolwin.h>
#include <wx/stattext.h>
#include <wx/html/htmlwin.h>
#include <wx/wxhtml.h>

#include "aui_includes/aui_includes.h"
#include "SpreadsheetWindow.h"

#define CEP_SIZE (wxSize(125, 250))

#define AED_SIZE (wxSize(340, 250))
#define AED_SIZE_MAX (wxSize(400, 280))

enum class CEP
{
	ID_REPS_SPINCTRL,
	ID_ADD_REPS,
	ID_REP_COUNTER
};

class CounterList;
class ExerciseNotebook; // Inherits from wxAuiNotebook, dockable & movable tabs will be nice for the user
class HtmlPanelCover;

class CustomExercisePanel: public wxPanel
{
private:
	wxString m_exerciseName;

	// Sizers
	wxFlexGridSizer* m_pControlSizer;
	wxStaticBoxSizer* m_pTopSizer;
	wxStaticBox* m_pTopParent;

	// Controls
	wxSpinCtrl* m_pSpinCtrl;
	wxBitmapButton* m_pAddButton;
	wxBitmapButton* m_pSaveButton;
	CounterList* m_pCounterList;

	// Validator
	int m_repCount;

public:
	CustomExercisePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = CEP_SIZE,
		long style = 0L);
	~CustomExercisePanel();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnAddReps(wxCommandEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
};

class TimedExercisePanel: public wxPanel
{
private:
	wxString m_exerciseName;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pDurationSizer;
	wxBoxSizer* m_pButtonSizer;
	wxFlexGridSizer* m_pMiscInfoSizer;

	// Controls
	wxBitmapButton* m_pAddButton;
	wxBitmapButton* m_pSaveButton;
	CounterList* m_pCounterList;

	wxSpinCtrl* m_pHourCtrl; 
	wxSpinCtrl* m_pMinCtrl; 
	wxSpinCtrl* m_pSecCtrl; 

	// Text
	wxStaticText* m_pDurationTxt;
	wxStaticText* m_pMiscInfoTxt;

	// Validation
	int m_hours;
	int m_mins;
	int m_secs;

public:
	TimedExercisePanel(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = CEP_SIZE,
		long style = 0L);
	~TimedExercisePanel();

	// Getters
	const int GetHours() const { return m_hours; }
	const int GetMins() const { return m_mins; }
	const int GetSecs() const { return m_secs; }

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnAdd(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
};

class AddExerciseDialog: public wxDialog
{
private:
	// Controls
	wxTextCtrl* m_pExerciseNameTxt;
	wxCheckBox* m_pTimeChk;
	wxButton* m_pOk;
	wxButton* m_pCancel;
	wxButton* m_pSearchImg;
	wxBitmap m_image;

	wxStaticText* m_pImageLabel;

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxFlexGridSizer* m_pHorizontalSizer;
	wxFlexGridSizer* m_pButtonSizer;

	// Members for initializing outside of the class
	wxString m_imagePath;
	wxBitmapType m_bitmapType;

	// Validator
	wxString m_exerciseName;
	bool m_bUseImage{ false };
	bool m_bTimedExercise{ false };

public:
	AddExerciseDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Add Exercise"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);
	~AddExerciseDialog();

	// Getters
	const bool UseImage() const { return m_bUseImage; }
	const wxBitmapType GetBitmapType() const { return m_bitmapType; }
	const wxString& GetImagePath() const { return m_imagePath; }
	const wxString& GetExerciseName() const { return m_exerciseName; }
	const bool GetTimed() const { return m_bTimedExercise; }
	const wxBitmap& GetImage() const
	{
		if (m_image.IsOk())
			return m_image;
		else
			return wxNullBitmap;
	}

	void CustomRefresh();

	// Setup
	void Init();
	void SetupSizing();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnOK(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnEnter(wxCommandEvent& event);
	void OnSearch(wxCommandEvent& event);
	void OnCheck(wxCommandEvent& event);
};

class DynamicPlan: public wxScrolled<wxPanel>
{
private:
	// Controls
	wxButton* m_pAddExercise; wxBitmap m_addBmp;
	wxButton* m_pOpenSpreadSheet; wxBitmap m_spreadsheetBmp;
	AddExerciseDialog* m_pAddExerciseDialog;
	SpreadsheetWindow* m_pSpreadsheetWindow;

	HtmlPanelCover* m_pHtmlPanelCover;
	bool m_bShowCover{ true };

	// Sizers
	wxBoxSizer* m_pTopSizer;
	wxBoxSizer* m_pTopButtonSizer;

	// AUI
	ExerciseNotebook* m_pExerciseNotebook;
	wxAuiManager m_auiMgr;
	wxString m_perspective;
	wxString m_defPerspective;

public:
	DynamicPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxVSCROLL | wxALWAYS_SHOW_SB);
	~DynamicPlan();

	// Setup
	void Init();
	void SetupControls();
	void SetupSizers();

	// Events
	void OnAddExercise(wxCommandEvent& event);
	void OnOpenSpreadsheet(wxCommandEvent& event);
};

class ExerciseNotebook: public wxAuiNotebook
{
private:
	wxImageList* m_pImageList;
	wxMenu* m_pTabMenu;

	long m_selectionIndex;
	int m_currentImageIndex{ -1 };

public:
	ExerciseNotebook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxAUI_NB_DEFAULT_STYLE);
	~ExerciseNotebook();

	void Init();
	void SetupMenu();
	void SetupImageList();

	void AddExercisePage(CustomExercisePanel* pExercisePanel, const wxString& title, bool bUseImage);
	void AddExercisePage(TimedExercisePanel* pTimedPanel, const wxString& title, bool bUseImage);
	void AddImageToList(const wxBitmap& bmp);

	// Events
	void OnCloseTabMenu(wxCommandEvent& event);
	void OnCloseTab(wxAuiNotebookEvent& event);
	void OnRightClickTab(wxAuiNotebookEvent& event);
	void OnPageChange(wxAuiNotebookEvent& event);
};

class HtmlPanelCover: public wxPanel
{
public:
	HtmlPanelCover(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif