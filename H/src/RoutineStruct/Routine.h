#ifndef _ROUTINESTRUCT_H_
#define _ROUTINESTRUCT_H_

#include <utility>
#include <wx/wx.h>

#define ROUTINE_LIST_SIZE ( 7 )

struct Routine
{
	wxString m_daysOfWeek[ROUTINE_LIST_SIZE];
};

#endif