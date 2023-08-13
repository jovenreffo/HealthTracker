#include "GridCommand.h"

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
