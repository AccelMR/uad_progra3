#pragma once

#include "CApp.h"
#include "..\Include\CCamera.h"
#include "Globals.h"
#include "..\Include\C3DModel.h"
#include "..\Include\CWorld.h"
#include <Windows.h>

class CAppProyectoP3 : public CApp
{
private:
	CWorld *myWorld;

	// Current delta time (time of the current frame - time of the last frame)
	//double m_currentDeltaTime;

	// Current object rotation, expressed in degrees
	//double m_objectRotation;

	// Current object position
	//CVector3 m_objectPosition;

	//  Object rotation speed (degrees per second)
	//double m_rotationSpeed;

	// Pointer to an object of type C3DModel
	//C3DModel *m_p3DModel;

public:
	CAppProyectoP3();
	CAppProyectoP3(int window_width, int window_height);
	~CAppProyectoP3();

	 void onMouse(float deltaX, float deltaY);
	 void onF3(int mods);

	 void moveCamera(float direction);

	 void update(double delta_time);
	 void run();
	 void render();
	 bool initializeMenu();
};

