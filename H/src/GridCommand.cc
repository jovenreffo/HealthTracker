#include "GridCommand.h"

// ===== GridCellState =====

GridCellState::GridCellState(int row, int col, const wxString& cellValue, const wxFont& cellFont, const wxSize& cellSize, const wxColour& colour)
	: m_row{ row }, m_col{ col }, m_cellValue{ cellValue }, m_cellFont{ cellFont }, m_cellSize{ cellSize }, m_cellBackgroundColour{ colour }
{
	// this signifies an instance of this class has been initiated, use this bool to check if it is active
	m_bActive = true;
}

// ===== GridCommand =====

GridCommand::GridCommand(wxGrid* pGrid, bool bCanUndo, const wxString& name)
	: wxCommand(bCanUndo, name), m_pGrid{ pGrid }
{

}

bool GridCommand::CanUndo() const
{
	return false;
}

wxString GridCommand::GetName() const
{
	return wxString();
}

bool GridCommand::Undo()
{
	return false;
}