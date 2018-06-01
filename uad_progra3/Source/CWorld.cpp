#include "..\Include\CWorld.h"


CWorld::CWorld(COpenGLRenderer *openGLRenderer) :
	OpenGLRenderer(openGLRenderer),
	myQuadTree (nullptr),
	myHexGrid (nullptr),
	initialized (false)
{
	m_TextureNames.resize(4);
	m_TextureNames = { TEX_WORLD_1,TEX_WORLD_2,TEX_WORLD_3,TEX_WORLD_4 };
	m_TexturesID = { 0,0,0,0 };
}


CWorld::~CWorld()
{
}

bool CWorld::Initialize()
{
	myHexGrid = new CHexGrid();
	if (myHexGrid->Inicialize(OpenGLRenderer)) {
		initialized = true;
	}


	//for (size_t i = 0; i < 4; i++)
	//{
		std::wstring wresourceFiletexture;
		std::string resourceFileTexture;
		// If resource files cannot be found, return
		if (!CWideStringHelper::GetResourceFullPath(TEX_WORLD_1, wresourceFiletexture, resourceFileTexture))
		{
			Log << "ERROR: Unable to find one or more resource textures: " << endl;
		}
		TGAFILE tgaFile;
		tgaFile.imageData = NULL;
		unsigned int aiuda = -1;
		if (LoadTGAFile(resourceFileTexture.c_str(), &tgaFile))
		{
			if (tgaFile.imageData == NULL ||
				tgaFile.imageHeight < 0 ||
				tgaFile.imageWidth < 0)
			{
				if (tgaFile.imageData != NULL)
				{
					delete[] tgaFile.imageData;
				}
				return false;
			}

			// Create a texture object for the menu, and copy the texture data to graphics memory
			if (!OpenGLRenderer->createTextureObject(
				&aiuda,
				tgaFile.imageData,
				tgaFile.imageWidth,
				tgaFile.imageHeight
			))
			{
				return false;
			}

			// Texture data is stored in graphics memory now, we don't need this copy anymore
			if (tgaFile.imageData != NULL)
			{
				delete[] tgaFile.imageData;
			}
		}
		else
		{
			// Free texture data
			if (tgaFile.imageData != NULL)
			{
				delete[] tgaFile.imageData;
			}

			return false;
		}
		OpenGLRenderer->initializeMCCube(aiuda);
	//}

	//myHexGrid->createTextureWorld(&m_TexturesID);

	return initialized;
}

void CWorld::render(CVector3 CamPosition)
{
	float color[3] = { 0.95f, 0.95f, 0.95f };
	for (size_t i = 0; i < SIZE_OF_HEXGRID; i++)
	{
		for (size_t j = 0; j < SIZE_OF_HEXGRID; j++)
		{

			float x, y, z;
			x = myHexGrid->getCenter(i, j).getX() + CamPosition.getX();
			y = myHexGrid->getCenter(i, j).getY() + CamPosition.getY();
			z = myHexGrid->getCenter(i, j).getZ() + CamPosition.getZ();
			MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, CVector3(x,y,z));

			OpenGLRenderer->renderMCCube(
			&modelMatrix
			);
		}
	}

	//MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)0, CamPosition);
	//OpenGLRenderer->renderWireframeObject(
	//	myHexGrid->getShaderProgramId(),
	//	myHexGrid->getVAOID(),
	//	myHexGrid->getNumIndices(),
	//	color,
	//	&modelMatrix
	//);

}

bool CWorld::isInitialized()
{
	return this->initialized;
}

void CWorld::DefaultWorld()
{
	cout << "Create World " << endl;
}

bool CWorld::InitializeQuadTree()
{
	myQuadTree = new CQuadTree(myHexGrid);
	myQuadTree->Inicialize();
	cout << "Create QuadTree " << endl;
	return true;
}
