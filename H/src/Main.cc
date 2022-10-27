#include "Window.h"

wxIMPLEMENT_APP(App);
bool App::OnInit()
{
	wxInitAllImageHandlers();

	Frame* frame = new Frame();
	frame->Show(true);

	return true;
}