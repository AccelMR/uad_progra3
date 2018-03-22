#pragma once

#include <iostream>
#include "..\Include\CLogger.h"
#include "..\Include\CVector3.h"

class CHexGridCell
{
public:
	CHexGridCell(float x, float y, const float size, float a);
	~CHexGridCell();

	CVector3 getCenter();

	unsigned int * getGraphicMemoryObjectId();

	void getVertices(float* v);

private:

	unsigned int *graphicMemoryObjectId;

	CVector3 m_vertex [6];
	CVector3 m_center;
};
