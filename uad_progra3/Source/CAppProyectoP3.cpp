#include "..\Include\CAppProyectoP3.h"
#include "../Include/Globals.h"
#include "../Include/CAppParcial2.h"
#include "../Include/C3DModel.h"
#include "../Include/LoadTGA.h"
#include "../Include/CWideStringHelper.h"



CAppProyectoP3::CAppProyectoP3()
{
	Log << "CAppProyecto3" << endl;
}


CAppProyectoP3::~CAppProyectoP3()
{
}

void CAppProyectoP3::onMouse(float deltaX, float deltaY)
{
	CCamera* cam = getCamera();

	if (cam != nullptr) {
		cam->move(deltaX, deltaY);	
	}
}

void CAppProyectoP3::update(double deltaTime)
{
}

void CAppProyectoP3::run()
{
}

void CAppProyectoP3::render()
{
}

bool CAppProyectoP3::initializeMenu()
{
	return false;
}
