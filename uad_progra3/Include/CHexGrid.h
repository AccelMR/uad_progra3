#pragma once

#include <iostream>
#include <vector>
#include "..\Include\CLogger.h"
#include "..\Include\CVector3.h"
#include "..\Include\CHexGridCell.h"
#include "..\Include\COpenGLRenderer.h"
#include "..\Include\Globals.h"

#define SIZE_OF_HEXGRID 100


class CHexGrid
{
public:
	CHexGrid();
	~CHexGrid();

	bool Inicialize(COpenGLRenderer *openGLRenderer);

	unsigned int* getShaderProgramId();
	unsigned int* getVAOID();
	int getNumIndices();

private:
	CHexGridCell * m_hexLayout[SIZE_OF_HEXGRID][SIZE_OF_HEXGRID];

	const float size = 1.0f;
	const float radius = 0.8660254038f;

	unsigned int gridShaderProgramID;
	unsigned int gridVAOID;
};