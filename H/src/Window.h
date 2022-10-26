#pragma once

#include <wx/wx.h>
#include "ListBook.h"

class App : public wxApp
{
public:
	virtual bool OnInit();
};

#define WINDOW_SIZE (wxSize(640, 480))

class Frame : public wxFrame
{
private:
	DECLARE_EVENT_TABLE()

private:
	wxMenuBar* m_pMenuBar;
	wxMenu* m_pFileMenu;

	Listbook* m_pListbook;

public:
	Frame();

	// Window setup
	void Init();
	void SetupMenuBar();
	void SetupSizes();
	void SetupListbook();

	// Events
	void OnExit(wxCommandEvent& event);
};