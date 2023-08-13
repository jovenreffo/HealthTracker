#pragma once

#include <wx/cmdproc.h>
#include <wx/grid.h>
#include <wx/wx.h>

class GridCommand: public wxCommand
{
private:
	wxGrid* m_pGrid;

public:
	GridCommand(wxGrid* pGrid, bool bCanUndo, const wxString& name);
	
	// Overload functions
	bool CanUndo() const override;
	wxString GetName() const override;
	bool Undo() override;
};