#include "GridCommand.h"

// ===== GridCellState =====

GridCellState::GridCellState(const wxString& cellValue, const wxString& cellFont, const wxSize& cellSize, const wxColour& colour)
	: m_cellValue{ cellValue }, m_cellFont{ cellFont }, m_cellSize{ cellSize }, m_cellBackgroundColour{ colour }
{

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