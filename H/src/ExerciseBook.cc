#include "ExerciseBook.h"
#include "StandardPath.hpp"

ExerciseBook::ExerciseBook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxNotebook(parent, id, pos, size, style)
{
	this->Init();
}

void ExerciseBook::Init()
{
	this->SetupBitmaps();
	this->SetupPanels();
	this->SetupPages();
}

void ExerciseBook::SetupBitmaps()
{
	m_pImgList = new wxImageList(30, 30);
	m_workoutBmp = wxBitmap(path_data::dataDir + _T("\\Images\\workout.png"), wxBITMAP_TYPE_PNG);
	m_nutrBmp = wxBitmap(path_data::dataDir + _T("\\Images\\nutrition.png"), wxBITMAP_TYPE_PNG);

	m_workoutBmp.ResetAlpha();
	m_nutrBmp.ResetAlpha();

	m_pImgList->Add(m_workoutBmp);
	m_pImgList->Add(m_nutrBmp);
	this->AssignImageList(m_pImgList);
}

void ExerciseBook::SetupPanels()
{
	m_pWPPanel = new WPNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pNutrPanel = new NutritionPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
}

void ExerciseBook::SetupPages()
{
	this->AddPage(m_pWPPanel, _T("Workout Plan"), true, 0);
	this->AddPage(m_pNutrPanel, _T("Nutrition"), false, 1);
}