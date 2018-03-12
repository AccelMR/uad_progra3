#include "..\Include\CHexGrid.h"

CHexGrid::CHexGrid()
{
}

CHexGrid::~CHexGrid()
{
}

bool CHexGrid::Inicialize()
{
	for (int i  = 0; i  < 2; i++) {
		for (int j = 0; j < 2; j++) {

			if (i == 0) {
				if (j == 0) { m_hexLayout[i][j] = new CHexGridCell(i, j); }
				m_hexLayout[i][j] = new CHexGridCell(i, j + 1);				
			}

			else if (i % 2 == 0) {
				if (j == 0) { m_hexLayout[i][j] = new CHexGridCell(i + .5, j); }
				m_hexLayout[i][j] = new CHexGridCell(i + .5, j + 1);
			}

			else {
				if (j == 0) { m_hexLayout[i][j] = new CHexGridCell(i + 0.5, j + 1); }
				m_hexLayout[i][j] = new CHexGridCell(i + 0.5, j + 2);
			}
		}
	}
	return true;
}
