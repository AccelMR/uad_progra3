#include "..\Include\CWorld.h"



CWorld::CWorld(COpenGLRenderer *openGLRenderer) :
	OpenGLRenderer(openGLRenderer),
	myQuadTree(nullptr)
{
	myHexGrid = nullptr;
	initialized = false;
}


CWorld::~CWorld()
{
}

bool CWorld::Initialize()
{
	myHexGrid = new CHexGrid();
	if (myHexGrid->Inicialize(OpenGLRenderer)) {
		initialized = true;
		myQuadTree = new CQuadTree(myHexGrid);
		myQuadTree->initialized();
		return true;
	}
	return false;
}

void CWorld::render(CVector3 CamPosition)
{
	float color[3] = { 0.95f, 0.95f, 0.95f };
	MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, CamPosition);

	OpenGLRenderer->renderWireframeObject(
		myHexGrid->getShaderProgramId(),
		myHexGrid->getVAOID(),
		myHexGrid->getNumIndices(),
		color,
		&modelMatrix
	);
}

bool CWorld::isInitialized()
{
	return this->initialized;
}
