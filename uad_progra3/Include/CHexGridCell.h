#pragma once

#include <iostream>
#include "..\Include\CLogger.h"
#include "..\Include\CVector3.h"

class CHexGridCell
{
public:
	CHexGridCell(float x, float y);
	~CHexGridCell();

	CVector3 getCenter();

	unsigned int * getGraphicMemoryObjectId();

	void getVertices(float* v);

private:
	const float size = 1;
	const float radius = 1;

	unsigned int *graphicMemoryObjectId;

	CVector3 m_vertex [6];
	CVector3 m_center;

	//float m_verticesRaw[18];


};
