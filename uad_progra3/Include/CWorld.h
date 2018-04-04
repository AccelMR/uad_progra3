#pragma once

#include "..\Include\CWorld.h"
#include "..\Include\CHexGrid.h"
#include "..\Include\CGameMenu.h"
#include "..\Include\CApp.h"
#include "..\Include\CQuadTree.h"

class CWorld
{
private: 
	COpenGLRenderer * const OpenGLRenderer;
	CQuadTree *myQuadTree;
	bool initialized;

	CHexGrid *myHexGrid;
	//CGameWindow *menu;

public:
	CWorld(COpenGLRenderer *openGLRenderer);
	~CWorld();

	bool Initialize();
	void render(CVector3 CamPosition);
	bool isInitialized();
};

