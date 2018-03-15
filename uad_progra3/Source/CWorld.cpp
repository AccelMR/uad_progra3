#include "..\Include\CWorld.h"



CWorld::CWorld(COpenGLRenderer *openGLRenderer) :
	OpenGLRenderer(openGLRenderer)
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
		return true;
	}
	return false;
}

void CWorld::render()
{
	CVector3 camPos(0, 0, 0);
	float color[3] = { 0.95f, 0.95f, 0.95f };
	MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, camPos);

	OpenGLRenderer->renderObject(
		myHexGrid->getShaderProgramId(),
		myHexGrid->getVAOID(),
		myHexGrid->getNumFaces(),
		color,
		&modelMatrix
	);
}

bool CWorld::isInitialized()
{
	return this->initialized;
}
