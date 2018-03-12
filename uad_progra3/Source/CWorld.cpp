#include "..\Include\CWorld.h"



CWorld::CWorld()
{
	myHexGrid = nullptr;
}


CWorld::~CWorld()
{
}

bool CWorld::Initialize()
{
	myHexGrid = new CHexGrid;
	if(myHexGrid->Inicialize()) return true;
	return false;
}
