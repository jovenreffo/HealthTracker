#include "Window.h"

wxIMPLEMENT_APP(App);
bool App::OnInit()
{
	wxInitAllImageHandlers();

	Frame* frame = new Frame();
	frame->Show(true);
	
	this->SetVendorName(_T("Health++"));
	this->SetAppName(_T("Health++"));

	// Handle config setup
	wxConfigBase* pConfig = wxConfigBase::Get();
	pConfig->SetRecordDefaults();

	return true;
}

int App::OnExit()
{
	delete wxConfigBase::Set(nullptr);

	return 0;
}
