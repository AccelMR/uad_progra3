#pragma once

#include "..\Include\CWorld.h"
#include "..\Include\CHexGrid.h"
#include "..\Include\CGameMenu.h"
#include "..\Include\CApp.h"
#include "..\Include\CQuadTree.h"
#include "..\Include\Globals.h"
#include "..\Include\CWideStringHelper.h"
#include "..\Include\LoadTGA.h"

class CWorld
{
private: 
	COpenGLRenderer * const OpenGLRenderer;
	CQuadTree *myQuadTree;
	bool initialized;



	CHexGrid *myHexGrid;
	//CGameWindow *menu;

	vector<string> m_TextureNames;
	vector<unsigned int> m_TexturesID;

	static DWORD WINAPI InitilizeHexGrid(PVOID pvParam);

public:
	CWorld(COpenGLRenderer *openGLRenderer);
	~CWorld();

	bool Initialize();
	void render(CVector3 CamPosition);
	bool isInitialized();
	COpenGLRenderer* const getOpenGlrenderer() { return this->OpenGLRenderer; }

	CHexGrid* getMyGrid() { return this->myHexGrid; }

	void DefaultWorld();
	bool InitializeQuadTree();

};

