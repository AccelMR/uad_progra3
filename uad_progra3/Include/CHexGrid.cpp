#include "CHexGrid.h"

CHexGrid::CHexGrid()
{
}

CHexGrid::~CHexGrid()
{
}

void CHexGrid::Inicialize()
{
	for (int i = 0; i  < 100; i++) {
		for (int j = 0; j < 100; j++) {
			m_hexLayout[i][j] = new CHexGridCell(i, j);
		}
	}
}
