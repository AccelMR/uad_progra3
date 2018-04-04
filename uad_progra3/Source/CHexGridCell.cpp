#include "..\Include\CHexGridCell.h"


CHexGridCell::CHexGridCell(float x, float y, const float size, float a) :
	graphicMemoryObjectId(nullptr)
{
	center.setValues(x, 0, y);

	// Set vertex points
	vertex[0].setValues(x + (size / 2.0f),	0,      y - a);			// P0
	vertex[1].setValues(x + size,				0,		y	 );		// P1
	vertex[2].setValues(x + (size / 2.0f),	0,      y + a);			// P2
	vertex[3].setValues(x - (size / 2.0f),	0,      y + a);			// P3
	vertex[4].setValues(x - size,				0,		y	 );		// P4
	vertex[5].setValues(x - (size / 2.0f),	0,      y - a);			// P5
	
}

CHexGridCell::~CHexGridCell()
{

}

CVector3 CHexGridCell::getCenter()
{
	return this->center;
}

unsigned int * CHexGridCell::getGraphicMemoryObjectId()
{
	return graphicMemoryObjectId;
}

void CHexGridCell::getVertices(float * v)
{
	v[0]  = vertex[0].getX();
	v[1]  = vertex[0].getY();
	v[2]  = vertex[0].getZ();
	v[3]  = vertex[1].getX();
	v[4]  = vertex[1].getY();
	v[5]  = vertex[1].getZ();
	v[6]  = vertex[2].getX();
	v[7]  = vertex[2].getY();
	v[8]  = vertex[2].getZ();
	v[9]  = vertex[3].getX();
	v[10] = vertex[3].getY();
	v[11] = vertex[3].getZ();
	v[12] = vertex[4].getX();
	v[13] = vertex[4].getY();
	v[14] = vertex[4].getZ();
	v[15] = vertex[5].getX();
	v[16] = vertex[5].getY();
	v[17] = vertex[5].getZ();
}

CVector3 CHexGridCell::getPoint(int point)
{
	return vertex[point];
}
