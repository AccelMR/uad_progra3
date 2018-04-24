#include "..\Include\CWorld.h"


CWorld::CWorld(COpenGLRenderer *openGLRenderer) :
	OpenGLRenderer(openGLRenderer),
	myQuadTree (nullptr),
	myHexGrid (nullptr),
	initialized (false)
{
	m_TextureNames.resize(4);
	m_TextureNames = { TEX_WORLD_1,TEX_WORLD_2,TEX_WORLD_3,TEX_WORLD_4 };
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

	std::wstring wresourceFilenameVS;
	std::string resourceFilenameVS;
	TGAFILE tgaFile;
	tgaFile.imageData = NULL;

	for (size_t i = 0; i < 4; i++)
	{
		// If resource files cannot be found, return
		if (!CWideStringHelper::GetResourceFullPath(m_TextureNames[i].c_str(), wresourceFilenameVS, resourceFilenameVS))
		{
			Log << "ERROR: Unable to find one or more resource textures: " << endl;
			Log << "  " << VERTEX_SHADER_WIREFRAME << endl;
			Log << "  " << FRAGMENT_SHADER_WIREFRAME << endl;
		}

		if (LoadTGAFile(m_TextureNames[i].c_str(), &tgaFile))
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
				&m_TexturesID[i],
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

	}

	myHexGrid->createTextureWorld(&m_TexturesID);

	return initialized;
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
