#pragma once

#include <iostream>
#include "..\Include\CLogger.h"
#include "..\Include\CVector3.h"

class CHexGridCell
{
public:
	CHexGridCell(int x, int y);
	~CHexGridCell();

	CVector3 getCenter();

private:
	const float size	= 1.0f;
	const float radius	= 1.0f;

	CVector3 m_vertex [6];
	CVector3 m_center;

};
