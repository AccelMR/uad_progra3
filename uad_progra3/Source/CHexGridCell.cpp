#include "..\Include\CHexGridCell.h"


CHexGridCell::CHexGridCell(float x, float y, const float size, float a) :
	graphicMemoryObjectId(nullptr)
{
	//a = (sqrt(3))*size / 2;
	// Set vertex points
	m_vertex[0].setValues(x + (size / 2.0f), 0,     y - a);    // P0
	m_vertex[1].setValues(x + size,			 0,		y		  );	// P1
	m_vertex[2].setValues(x + (size / 2.0f), 0,     y + a);    // P2
	m_vertex[3].setValues(x - (size / 2.0f), 0,     y + a);	// P3
	m_vertex[4].setValues(x - size,			 0,		y		  );	// P4
	m_vertex[5].setValues(x - (size / 2.0f), 0,     y - a);	// P5

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

unsigned int * CHexGridCell::getGraphicMemoryObjectId()
{
	return graphicMemoryObjectId;
}

void CHexGridCell::getVertices(float * v)
{
	v[0] = m_vertex[0].getX();
	v[1] = m_vertex[0].getY();
	v[2] = m_vertex[0].getZ();
	v[3] = m_vertex[1].getX();
	v[4] = m_vertex[1].getY();
	v[5] = m_vertex[1].getZ();
	v[6] = m_vertex[2].getX();
	v[7] = m_vertex[2].getY();
	v[8] = m_vertex[2].getZ();
	v[9] = m_vertex[3].getX();
	v[10] = m_vertex[3].getY();
	v[11] = m_vertex[3].getZ();
	v[12] = m_vertex[4].getX();
	v[13] = m_vertex[4].getY();
	v[14] = m_vertex[4].getZ();
	v[15] = m_vertex[5].getX();
	v[16] = m_vertex[5].getY();
	v[17] = m_vertex[5].getZ();
}
