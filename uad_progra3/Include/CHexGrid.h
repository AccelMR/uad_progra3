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

	bool Inicialize();

private:

	CHexGridCell *m_hexLayout [3][3];
};