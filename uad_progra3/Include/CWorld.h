#pragma once

#include "..\Include\CWorld.h"
#include "..\Include\CHexGrid.h"

class CWorld
{
private: 
	CHexGrid *myHexGrid;
public:
	CWorld();
	~CWorld();

	bool Initialize();
};

