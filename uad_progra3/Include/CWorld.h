#pragma once

#include "..\Include\CWorld.h"
#include "..\Include\CHexGrid.h"
#include "..\Include\CGameMenu.h"
#include "..\Include\CApp.h"

class CWorld
{
private: 
	COpenGLRenderer * const OpenGLRenderer;
	bool initialized;

	CHexGrid *myHexGrid;
	//CGameWindow *menu;

public:
	CWorld(COpenGLRenderer *openGLRenderer);
	~CWorld();

	bool Initialize();
	void render();
	bool isInitialized();
};

