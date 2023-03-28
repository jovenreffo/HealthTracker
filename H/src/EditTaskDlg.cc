#include <wx/valtext.h>
#include <wx/valgen.h>
#include <wx/stattext.h>
#include <wx/statline.h>

#include "EditTaskDlg.h"

EditTaskDlg::EditTaskDlg(int priorityLevel, const wxString& taskName, const wxString& taskDesc, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxDialog(parent, id, title, pos, size, style), m_taskName{ taskName }, m_taskDesc{ taskDesc }, m_priorityLevel{ priorityLevel }
{
	// Set the title to include the current taske name
	this->SetTitle(wxString(_T("Edit Task - ")) << m_taskName);

	this->Init();

	// Event binding
	m_pTaskName->Bind(wxEVT_TEXT_ENTER, &EditTaskDlg::OnEnter, this);
	m_pTaskName->Bind(wxEVT_TEXT_MAXLEN, &EditTaskDlg::OnMaxLengthName, this);
	m_pTaskDesc->Bind(wxEVT_TEXT_ENTER, &EditTaskDlg::OnEnter, this);
	m_pTaskDesc->Bind(wxEVT_TEXT_MAXLEN, &EditTaskDlg::OnMaxLengthDesc, this);

	m_pPriorityLevel->Bind(wxEVT_CHOICE, &EditTaskDlg::OnChoice, this);

	m_pOk->Bind(wxEVT_BUTTON, &EditTaskDlg::OnOK, this);
	m_pCancel->Bind(wxEVT_BUTTON, &EditTaskDlg::OnCancel, this);
}

EditTaskDlg::~EditTaskDlg()
{
	// Unbind events
	m_pTaskName->Unbind(wxEVT_TEXT_ENTER, &EditTaskDlg::OnEnter, this);
	m_pTaskName->Unbind(wxEVT_TEXT_MAXLEN, &EditTaskDlg::OnMaxLengthName, this);
	m_pTaskDesc->Unbind(wxEVT_TEXT_ENTER, &EditTaskDlg::OnEnter, this);
	m_pTaskDesc->Unbind(wxEVT_TEXT_MAXLEN, &EditTaskDlg::OnMaxLengthDesc, this);

	m_pPriorityLevel->Unbind(wxEVT_CHOICE, &EditTaskDlg::OnChoice, this);

	m_pOk->Unbind(wxEVT_BUTTON, &EditTaskDlg::OnOK, this);
	m_pCancel->Unbind(wxEVT_BUTTON, &EditTaskDlg::OnCancel, this);
}

void EditTaskDlg::Init()
{
	this->SetupPriorityLevels();
	this->SetupControls();
	this->SetupSizers();
	this->SetupSizing();
}

void EditTaskDlg::SetupPriorityLevels()
{
	m_priorityLevels.Add(_T("Minor"));
	m_priorityLevels.Add(_T("Medium"));
	m_priorityLevels.Add(_T("Major"));
}

void EditTaskDlg::SetupControls()
{
	m_pTaskName = new wxTextCtrl(this, wxID_ANY, m_taskName, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxTextValidator(0, &m_taskName));
	m_pTaskDesc = new wxTextCtrl(this, wxID_ANY, m_taskDesc, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER, wxTextValidator(0, &m_taskDesc));

	// Set max lengths
	m_pTaskName->SetMaxLength(35);
	m_pTaskDesc->SetMaxLength(100);

	m_pPriorityLevel = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_priorityLevels, 0L, wxGenericValidator(&m_priorityLevel));
	m_pPriorityLevel->SetSelection(m_priorityLevel);

	m_pOk = new wxButton(this, wxID_OK, _T("OK"), wxDefaultPosition, wxDefaultSize);
	m_pCancel = new wxButton(this, wxID_CANCEL, _T("Cancel"), wxDefaultPosition, wxDefaultSize);
}

void EditTaskDlg::SetupSizers()
{
	m_pTopSizer = new wxBoxSizer(wxVERTICAL);
	m_pControlSizer = new wxFlexGridSizer(2, wxSize(5, 1));
	m_pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizerAndFit(m_pTopSizer);

	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Task name:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pControlSizer->Add(m_pTaskName, wxSizerFlags().Left().Border(wxALL, 5));
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Task description:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pControlSizer->Add(m_pTaskDesc, wxSizerFlags().Left().Border(wxALL, 5));
	m_pControlSizer->Add(new wxStaticText(this, wxID_STATIC, _T("Priority level:")), wxSizerFlags().Left().Border(wxALL, 5));
	m_pControlSizer->Add(m_pPriorityLevel, wxSizerFlags().Left().Border(wxALL, 5));

	m_pButtonSizer->Add(m_pOk, wxSizerFlags().Left().Border(wxALL, 5));
	m_pButtonSizer->Add(m_pCancel, wxSizerFlags().Left().Border(wxALL, 5));

	m_pTopSizer->Add(m_pControlSizer);
	m_pTopSizer->Add(new wxStaticLine(this), wxSizerFlags().Expand().Border(wxALL, 5));
	m_pTopSizer->Add(m_pButtonSizer);
}

void EditTaskDlg::SetupSizing()
{
	this->SetInitialSize(ETD_SIZE);

	this->SetSize(this->DoGetBestSize());
	this->SetMinSize(this->DoGetBestSize());
}

void EditTaskDlg::HandleExit()
{
	if (Validate() && TransferDataFromWindow())
	{
		if (IsModal())
			EndModal(wxID_OK);
		else
		{
			SetReturnCode(wxID_OK);
			Show(false);
		}
	}
}

void EditTaskDlg::OnEnter(wxCommandEvent& e)
{
	this->HandleExit();
}

void EditTaskDlg::OnChoice(wxCommandEvent& e)
{
	m_priorityLevel = m_pPriorityLevel->GetSelection();
}

void EditTaskDlg::OnOK(wxCommandEvent& e)
{
	this->HandleExit();
}

void EditTaskDlg::OnCancel(wxCommandEvent& e)
{
	this->SetReturnCode(wxID_CANCEL);
	this->Show(false);
}

void EditTaskDlg::OnMaxLengthName(wxCommandEvent& e)
{
	wxMessageBox(_T("You have reached the character limit."), _T("Warning"), wxOK | wxICON_EXCLAMATION);
	e.Skip();
}

void EditTaskDlg::OnMaxLengthDesc(wxCommandEvent& e)
{
	wxMessageBox(_T("You have reached the character limit."), _T("Warning"), wxOK | wxICON_EXCLAMATION);
	e.Skip();
}
