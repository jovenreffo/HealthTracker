#include "DynamicPlan.h"
#include "StandardPath.hpp"

CustomExercisePanel::CustomExercisePanel(const wxString& exerciseName, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style), m_exerciseName{ exerciseName }
{
	this->Init();
}

CustomExercisePanel::~CustomExercisePanel()
{

}

void CustomExercisePanel::Init()
{
	this->SetupControls();
	this->SetupSizers();
}

void CustomExercisePanel::SetupControls()
{

}

void CustomExercisePanel::SetupSizers()
{
	m_pTopSizer = new wxStaticBoxSizer(wxVERTICAL, this, m_exerciseName);
	m_pTopParent = m_pTopSizer->GetStaticBox();
	this->SetSizerAndFit(m_pTopSizer);
}

// DynamicPlan

DynamicPlan::DynamicPlan(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxScrolled<wxPanel>(parent, id, pos, size, style, _T("DynamicPlanWin"))
{
	this->SetScrollRate(10, 10);
}
