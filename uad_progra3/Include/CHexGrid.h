#pragma once

#include <iostream>
#include <vector>
#include "..\Include\CLogger.h"
#include "..\Include\CVector3.h"
#include "..\Include\CHexGridCell.h"
#include "..\Include\COpenGLRenderer.h"
#include "..\Include\Globals.h"

#define SIZE_OF_HEXGRID 3


class CHexGrid
{
public:
	CHexGrid();
	~CHexGrid();

	bool Inicialize(COpenGLRenderer *openGLRenderer);

	unsigned int* getShaderProgramId();
	unsigned int* getVAOID();
	int getNumIndices();

	CVector3 getCellPointInfo(int x, int y, int point);

private:

	// Size of each side of hexagon
	// At the same time, it is the size from center to any vertex.
	const float sizeOfSide = 1.0f;

	// Size of line that goes from the center to the top/bottom edge
	float a;

	CHexGridCell * m_hexLayout[SIZE_OF_HEXGRID][SIZE_OF_HEXGRID];

	unsigned int gridShaderProgramID;
	unsigned int gridVAOID;

protected:

};