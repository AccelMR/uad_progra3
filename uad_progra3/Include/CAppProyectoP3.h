#pragma once

#include "CApp.h"
#include "..\Include\CCamera.h"

class CAppProyectoP3 : public CApp
{
private:
	//CWorld myWorld;

public:
	CAppProyectoP3();
	~CAppProyectoP3();

	virtual void onMouse(float deltaX, float deltaY);
};

