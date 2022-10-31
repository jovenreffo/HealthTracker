#include "ExercisePanel.h"

BEGIN_EVENT_TABLE(ExercisePanel, wxPanel)	

END_EVENT_TABLE()

ExercisePanel::ExercisePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
	: wxPanel(parent, id, pos, size, style)
{
	this->Init();
}

void ExercisePanel::Init()
{
	this->SetupExerciseBook();
	this->SetupSizers();
}

void ExercisePanel::SetupExerciseBook()
{
	m_pExerciseBook = new ExerciseBook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	m_pExerciseBook->Show(true);
}

void ExercisePanel::SetupSizers()
{
	// Initialization
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizerAndFit(m_pBoxSizer);

	// Add any elements
	m_pBoxSizer->Add(m_pExerciseBook, 1, wxEXPAND | wxALL, 5);
}
