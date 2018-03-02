#include "..\Include\CAppProyectoP3.h"



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
