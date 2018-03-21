#pragma once

#include <iostream>
#include <vector>
#include "..\Include\CLogger.h"
#include "..\Include\CVector3.h"
#include "..\Include\CHexGridCell.h"
#include "..\Include\COpenGLRenderer.h"
#include "..\Include\Globals.h"

#define SIZE_OF_HEXGRID 1


class CHexGrid
{
public:
	CHexGrid();
	~CHexGrid();

	bool Inicialize(COpenGLRenderer *openGLRenderer);

	unsigned int* getShaderProgramId();
	unsigned int* getVAOID();
	size_t getNumFaces();

private:
	CHexGridCell * m_hexLayout[SIZE_OF_HEXGRID][SIZE_OF_HEXGRID];

	unsigned int gridShaderProgramID;
	unsigned int gridVAOID;
};