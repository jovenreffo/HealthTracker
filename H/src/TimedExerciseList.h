#ifndef TIMEDEXERCISELIST_H
#define TIMEDEXERCISELIST_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>

struct TEL
{
	int m_hours;
	int m_mins;
	int m_secs;
	int m_cals;
	int m_distance;
};

class TimedExerciseList : public wxListView
{
private:
	TEL m_exerciseInfo;
	std::vector<TEL> m_TELVec;

	wxMenu* m_pMenu;
	wxImageList* m_pImageList;
	wxBitmap m_calorieBmp;

	int m_currentItemIndex;

public:
	TimedExerciseList(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxLC_REPORT | wxLC_SINGLE_SEL);
	~TimedExerciseList();

	void AddItem(const TEL& tel);

	// Getters
	const int GetHours() const { return m_exerciseInfo.m_hours; }
	const int GetMinutes() const { return m_exerciseInfo.m_mins; }
	const int GetSeconds() const { return m_exerciseInfo.m_secs; }
	const int GetCalories() const { return m_exerciseInfo.m_cals; }
	const int GetDistance() const { return m_exerciseInfo.m_distance; }

	const int GetHours(int i) const { return m_TELVec[i].m_hours; }
	const int GetMinutes(int i) const { return m_TELVec[i].m_mins; }
	const int GetSeconds(int i) const { return m_TELVec[i].m_secs; }
	const int GetCalories(int i) const { return m_TELVec[i].m_cals; }
	const int GetDistance(int i) const { return m_TELVec[i].m_distance; }

	// Setup
	void Init();
	void SetupMenu();
	void SetupColumns();
	void SetupImageList();

	// Events
	void OnSelectItem(wxListEvent& event);
	void OnRightClickItem(wxListEvent& event);
	void OnDeleteItem(wxCommandEvent& event);
};

#endif // !TIMEDEXERCISELIST_H