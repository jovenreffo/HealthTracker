#ifndef VIEWBUTTON_H
#define VIEWBUTTON_H

#include <wx/wx.h>
#include <wx/bmpbuttn.h>

#include "WorkoutWindow.h"
#include "WPLists.h"

class ViewButton : public wxBitmapButton
{
private:
	int m_uniqueID;
	int m_selection;
	wxString m_workoutName;

	// Workout information
	WorkoutList* m_pWorkoutList;

public:
	ViewButton(WorkoutList* pWorkoutList,
		const wxString& workoutName,
		int selection,
		int uniqueID,
		wxWindow* parent,
		wxWindowID id,
		const wxBitmap& bmp,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxBU_AUTODRAW);
	~ViewButton();

	void SetWorkoutName(const wxString& name) { m_workoutName = name; }

	// Click event
	void OnClick(wxCommandEvent& event);
};

#endif