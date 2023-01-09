#ifndef DYNAMICPLAN_H
#define DYNAMICPLAN_H

#include <wx/panel.h>
#include <wx/button.h>
#include "aui_includes/aui_includes.h"

#define LEP_SIZE (wxSize(125, 250))

class LoadedExercisePanel : public wxPanel
{
private:
	wxString m_exerciseName;

public:
	LoadedExercisePanel(const wxString& exerciseName,
		wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = LEP_SIZE,
		long style = 0L);
};

class DynamicPlan : public wxPanel
{
private:
	wxAuiManager m_auiMgr;

public:
	DynamicPlan(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0L);
};

#endif