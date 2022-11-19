#ifndef _ROUTINESTRUCT_H_
#define _ROUTINESTRUCT_H_

#include <utility>
#include <wx/wx.h>

#define CL_SIZE ( 7 )

struct Routine
{
	std::pair<int, wxString> m_pairs[CL_SIZE];

	const wxString& GetStringAt(int index) const { return m_pairs[index].second; }
};

#endif