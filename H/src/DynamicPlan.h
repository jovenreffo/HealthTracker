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

#define CEP_SIZE (wxSize(125, 250))

#define AED_SIZE (wxSize(280, 210))
#define AED_SIZE_MAX (wxSize(340, 200))

enum class CEP
{
	ID_REPS_SPINCTRL,
	ID_ADD_REPS,
	ID_REP_COUNTER
};

class CounterList;
class ExerciseNotebook; // Inherits from wxAuiNotebook, dockable & movable tabs will be nice for the user
class HtmlPanelCover;

class CustomExercisePanel : public wxPanel
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
};

class AddExerciseDialog : public wxDialog
{
private:
	// Controls
	wxTextCtrl* m_pExerciseNameTxt;
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

public:
	AddExerciseDialog(wxWindow* parent,
		wxWindowID id,
		const wxString& title = _T("Add Exercise"),
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX);

	// Getters
	const bool UseImage() const { return m_bUseImage; }
	const wxBitmapType GetBitmapType() const { return m_bitmapType; }
	const wxString& GetImagePath() const { return m_imagePath; }
	const wxString& GetExerciseName() const { return m_exerciseName; }
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
};

class DynamicPlan : public wxScrolled<wxPanel>
{
private:
	// Controls
	wxButton* m_pAddExercise; wxBitmap m_addBmp;
	wxButton* m_pOpenSpreadSheet; wxBitmap m_spreadsheetBmp;
	AddExerciseDialog* m_pAddExerciseDialog;

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

	void CustomRefresh();

	// Events
	void OnAddExercise(wxCommandEvent& event);
	void OnOpenSpreadsheet(wxCommandEvent& event);
};

class ExerciseNotebook : public wxAuiNotebook
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