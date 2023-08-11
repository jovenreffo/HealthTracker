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

	// Override functions
	int GetNumberRows() override;
	int GetNumberCols() override;
	bool IsEmptyCell(int r, int c) override;
	wxString GetValue(int r, int c) override;
	void SetValue(int r, int c, const wxString& value) override;
};

#endif