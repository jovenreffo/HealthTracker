#ifndef GRIDTABLEBASEDERIVATIVE_H
#define GRIDTABLEBASEDERIVATIVE_H

#include <wx/grid.h>
#include <wx/wx.h>

class GridTableBaseDerivative: public wxGridTableBase
{
private:
	wxGrid* m_pGrid;

public:
	GridTableBaseDerivative(wxGrid* pGrid);
};

#endif