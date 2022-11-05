#include <wx/sizer.h>
#include "SaveWorkoutDialog.h"

SaveWorkoutDialog::SaveWorkoutDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style)
{
	this->Init();
}

void SaveWorkoutDialog::Init()
{
	m_pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	m_pOk = new wxButton(this, wxID_OK, _T("OK"));
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"));

	this->SetupControls();
}

void SaveWorkoutDialog::SetupControls()
{
	wxBoxSizer* pTopSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* pTextSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->SetSizerAndFit(pTopSizer);
}
