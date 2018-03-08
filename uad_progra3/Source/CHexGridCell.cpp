#include "..\Include\CHexGridCell.h"


CHexGridCell::CHexGridCell(int x, int y)
{
	// Set vertex points
	m_vertex[0].setValues((float)x + (size / 2), 0, (float)y - radius);	// P1
	m_vertex[1].setValues((float)x + size, 0, (float)y);				// P2
	m_vertex[2].setValues((float)x + (size / 2), 0, (float)y + radius);	// P3
	m_vertex[3].setValues((float)x - (size / 2), 0, (float)y + radius);	// P4
	m_vertex[4].setValues((float)x - size, 0, y);						// P5
	m_vertex[5].setValues((float)x - (size / 2), 0, (float)y - radius);	// P6

	// Calculate center
	CVector3 xC, yC;
	xC = m_vertex[5] + ((m_vertex[5] + m_vertex[1]) / 2);
	yC = m_vertex[4] + ((m_vertex[4] + m_vertex[2]) / 2);
	
	m_center.setValues(xC.getX(), 0, yC.getZ());		


}

CHexGridCell::~CHexGridCell()
{

}

CVector3 CHexGridCell::getCenter()
{
	return this->m_center;
}
