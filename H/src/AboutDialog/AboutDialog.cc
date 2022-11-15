#include "AboutDialog.h"

AboutDialog::AboutDialog()
{
	m_developers.Add(_T("Joven Reffo"));

	m_info.SetName(_T("Health++"));
	m_info.SetVersion(_T("1.0.0 (Beta)"));
	m_info.SetDescription(_T("Health++ is program designed for individuals to easily track their health progress, and set goals they can achieve."));
	m_info.SetCopyright(_T("Copyright (c) 2022 Health++"));
	m_info.SetDevelopers(m_developers);

	wxAboutBox(m_info);
}
