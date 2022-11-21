#include "RoutineView.h"

BEGIN_EVENT_TABLE(RoutineView, wxDialog)


END_EVENT_TABLE()

RoutineView::RoutineView(const std::vector<Routine>& routineInfo, RoutineDialog* pRoutineDialog, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_routineInfo{ routineInfo }, m_pRoutineDialog{ pRoutineDialog }
{
}
