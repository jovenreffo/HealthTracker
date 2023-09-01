#pragma once

#include <wx/cmdproc.h>
#include <wx/grid.h>
#include <wx/wx.h>

// store the current 
class GridCellState
{
private:
	wxString m_cellValue;
	wxFont m_cellFont;
	wxSize m_cellSize; // number of rows & cols associated with the cell
	wxColour m_cellBackgroundColour;

public:
	GridCellState() = default;
	GridCellState(const wxString& cellValue,
		const wxString& cellFont,
		const wxSize& cellSize,
		const wxColour& colour);

	// Getters
	const wxString& GetCellValue() const { return m_cellValue; }
	const wxFont& GetCellFont() const { return m_cellFont; }
	const wxSize& GetCellSize() const { return m_cellSize; }
	const wxColour& GetCellColour() const{ return m_cellBackgroundColour; }
};

// class for taking action on the grid for undo/redo
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