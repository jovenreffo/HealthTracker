#include "GridTableBaseDerivative.h"

GridTableBaseDerivative::GridTableBaseDerivative(wxGrid* pGrid)
	: wxGridTableBase(), m_pGrid{ pGrid }
{

}

int GridTableBaseDerivative::GetNumberRows()
{
	return m_pGrid->GetNumberRows();
}

int GridTableBaseDerivative::GetNumberCols()
{
	return m_pGrid->GetNumberCols();
}

bool GridTableBaseDerivative::IsEmptyCell(int r, int c)
{
	return m_pGrid->GetCellValue(r, c).IsEmpty();
}

wxString GridTableBaseDerivative::GetValue(int r, int c)
{
	return m_pGrid->GetCellValue(r, c);
}

void GridTableBaseDerivative::SetValue(int r, int c, const wxString& value)
{
	m_pGrid->SetCellValue(r, c, value);
}