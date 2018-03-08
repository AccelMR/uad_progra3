#pragma once

#include <iostream>
#include <vector>
#include "..\Include\CLogger.h"
#include "..\Include\CVector3.h"
#include "..\Include\CHexGridCell.h"



class CHexGrid
{
public:
	CHexGrid();
	~CHexGrid();

	void Inicialize();

private:

	CHexGridCell *m_hexLayout [100][100];
};