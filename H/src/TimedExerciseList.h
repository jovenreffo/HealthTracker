#ifndef TIMEDEXERCISELIST_H
#define TIMEDEXERCISELIST_H

#include <wx/wx.h>
#include <wx/listctrl.h>

struct TEL
{
	int m_hours;
	int m_mins;
	int m_secs;
	int m_cals;
	double m_distance;
};

class TimedExerciseList : public wxListView
{
private:
	TEL m_exerciseInfo;

	wxMenu* m_pMenu;
	wxImageList* m_pImageList;
	wxBitmap m_calorieBmp;

public:
	TimedExerciseList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);

	void AddItem(const TEL& tel);

	// Setup
	void Init();
	void SetupMenu();
	void SetupColumns();
	void SetupImageList();
};

#endif // !TIMEDEXERCISELIST_H