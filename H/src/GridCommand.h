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
	int m_row;
	int m_col;

	bool m_bActive{ false };

public:
	GridCellState() = default;
	GridCellState(int row,
		int col,
		const wxString& cellValue,
		const wxFont& cellFont,
		const wxSize& cellSize,
		const wxColour& colour);

	// Getters
	bool IsActive() const { return m_bActive; }

	const int GetRow() const { return m_row; }
	const int GetCol() const { return m_col; }

	const wxString& GetCellValue() const { return m_cellValue; }
	const wxFont& GetCellFont() const { return m_cellFont; }
	const wxSize& GetCellSize() const { return m_cellSize; }
	const wxColour& GetCellColour() const{ return m_cellBackgroundColour; }

	// overload operator=
	GridCellState& operator=(const GridCellState& other)
	{
		// Protect against self assignment
		if (this == &other)
			return *this;

		// Copy the data
		this->m_row = other.m_row;
		this->m_col = other.m_col;
		this->m_cellValue = other.m_cellValue;
		this->m_cellFont = other.m_cellFont;
		this->m_cellSize = other.m_cellSize;
		this->m_cellBackgroundColour = other.m_cellBackgroundColour;
	}
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