#ifndef _ABOUTDIALOG_H_
#define _ABOUTDIALOG_H_

#include <wx/aboutdlg.h>

class AboutDialog
{
private:
	wxAboutDialogInfo m_info;
	wxArrayString m_developers;

public:
	AboutDialog();
};

#endif