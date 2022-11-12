#ifndef _EXERCISEBOOK_H_
#define _EXERCISEBOOK_H_

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/imaglist.h>
#include "NutritionPanel.h"
#include "WPNotebook.h"

#define EXERCISEBOOK_STYLE (wxNB_MULTILINE | wxNB_TOP)

class ExerciseBook: public wxNotebook
{
private:
	// Main panels
	WPNotebook* m_pWPPanel;
	NutritionPanel* m_pNutrPanel;

	// Icons
	wxImageList* m_pImgList;
	wxBitmap m_workoutBmp;
	wxBitmap m_nutrBmp;

public:
	ExerciseBook(wxWindow* parent,
		wxWindowID id,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = EXERCISEBOOK_STYLE);

	// Book setup
	void Init();
	void SetupBitmaps();
	void SetupPanels();
	void SetupPages();
};

#endif