#include "BugReport.h"

BugReport::BugReport(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
}

BugReport::~BugReport()
{
}
