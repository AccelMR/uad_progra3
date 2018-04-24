#pragma once

#include "CApp.h"
#include "..\Include\CCamera.h"
#include "Globals.h"
#include "..\Include\C3DModel.h"
#include "..\Include\CWorld.h"
#include <Windows.h>

#define DEFAULT_CAMERA_MOVE_SPEED 0.005
 
class CAppProyectoP3 : 
	public CApp
{
private:
	CWorld *myWorld;
	DWORD check;
	DWORD check2;
	DWORD threadID_1;
	HANDLE thread1;
	DWORD threadID_2;
	HANDLE thread2;
	DWORD threadID_3;
	HANDLE thread3;

	HANDLE hEvent;
	HANDLE hEvent2;
	bool init;

	// Current delta time (time of the current frame - time of the last frame)
	double m_currentDeltaTime;

	// Current object rotation, expressed in degrees
	double m_objectRotation;

	// Current object position
	CVector3 m_objectPosition;

	//  Object rotation speed (degrees per second)
	double m_rotationSpeed;

	// Pointer to an object of type C3DModel
	//C3DModel *m_p3DModel;

	static DWORD InitilizeWorld(PVOID pvParam);
	static DWORD InitilizeQuadTree(PVOID pvParam);
	static DWORD CreateDefaultWorld(PVOID pvParam);

public:
	CAppProyectoP3();
	CAppProyectoP3(int window_width, int window_height);
	~CAppProyectoP3();

	 void onMouseMove(float deltaX, float deltaY);
	 void onF3(int mods);

	 void moveCamera(float direction);

	 void update(double delta_time);
	 void run();
	 void render();
	 bool initializeMenu();
	 HANDLE getEvent() { return this->hEvent; }
	 HANDLE getEvent2() { return this->hEvent2; }

	 //double getRotation() {return this->m_}
};

