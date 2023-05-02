#include "ViewButton.h"

ViewButton::ViewButton(WorkoutList* pWorkoutList, const wxString& workoutName, int selection, int uniqueID, wxWindow* parent, wxWindowID id, const wxBitmap& bmp, const wxPoint& pos, const wxSize& size, long style)
	: wxBitmapButton(parent, id, bmp, pos, size, style), m_pWorkoutList{ pWorkoutList }, m_workoutName{ workoutName }, m_selection{ selection }, m_uniqueID{ uniqueID }
{
	this->Bind(wxEVT_BUTTON, &ViewButton::OnClick, this);
}

ViewButton::~ViewButton()
{
	this->Unbind(wxEVT_BUTTON, &ViewButton::OnClick, this);
}

void ViewButton::OnClick(wxCommandEvent& event)
{
	if (m_workoutName.empty())
	{
		wxMessageBox(_T("No workout to open."), _T("Notice"));
		return;
	}

	// Display a WorkoutWindow
	if (m_pWorkoutList)
	{
		m_pWorkoutList->OpenWorkout(m_workoutName);
	}
}