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
	const float size	= 0.5f;
	const float radius	= 0.4330127019;
	const float width	= 1.0f;
	const float horiz	= 0.75f;
	const float height	= 0.8660254038f;

	CVector3 m_vertex [6];
	CVector3 m_center;

};
