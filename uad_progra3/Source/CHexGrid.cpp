#include "..\Include\CHexGrid.h"
#include "..\Include\CWideStringHelper.h"


CHexGrid::CHexGrid() :
	gridShaderProgramID(0),
	gridVAOID(0)
{
	a = (sqrt(3))*sizeOfSide / 2;
}

CHexGrid::~CHexGrid()
{
	delete[] *m_hexLayout;
}

bool CHexGrid::Inicialize(COpenGLRenderer *openGLRenderer)
{
	// Temp array that saves XYZ of just one hexcell
	float v[6*3];

	// Array that saves XYZ of each hexcell
	float *verticesRaw = new float[sizeof(float)*(SIZE_OF_HEXGRID *SIZE_OF_HEXGRID * 6 * 3)];
	
	// Indices that indicates the order of triangles inner the hex
	unsigned short *indices = new unsigned short[3 * 4 * SIZE_OF_HEXGRID * SIZE_OF_HEXGRID];

	// Pos of first hexagon, calculates size of center
	float x = 0, y = 0;
	//if (SIZE_OF_HEXGRID % 2 == 0) {
	//	int hexDiv = SIZE_OF_HEXGRID / 2;
	//	x = -1*((sizeOfSide * 2 * hexDiv) + (hexDiv*sizeOfSide)) / 2;
	//	y = x;
	//}
	//else {
	//	int hexDiv = SIZE_OF_HEXGRID / 2;
	//	x = -1 * (((hexDiv + 1) * 2 * sizeOfSide) + (hexDiv*sizeOfSide)) / 2;
	//	y = x;
	//}

	// HexLayout, if center is even then it adds 1/2 to X(i) else (odd) it adds 1/2 to X(i) and 1 to Y(j)
	// Then it creates the VerticesRaw array. It has XYZ of each vertex
	size_t offset = 0;
	for (int i  = 0; i  < SIZE_OF_HEXGRID; i++) {
		for (int j = 0; j < SIZE_OF_HEXGRID; j++) {

			// First hexagon
			if (i == 0)
				if (j == 0)
					m_hexLayout[i][j] = new CHexGridCell(x, y, sizeOfSide, a);
			
			// http://webdevtipstricksandinfo.blogspot.mx/2012/08/creating-hexagonal-grid-for-games-c-java.html
			m_hexLayout[i][j] = new CHexGridCell(x + j * ((3 * sizeOfSide) / 2), y + (j % 2)*a + 2 * i*a, sizeOfSide, a);

			m_hexLayout[i][j]->getVertices(v);
			memcpy(&verticesRaw[offset], v, sizeof (float) * (6 * 3));
			offset += 6 * 3;
		}
	}

	unsigned short singleHexIndices[] = { 
		2,1,0,
		3,5,4,
		3,0,5,
		2,0,3 };

	size_t inOffset = 0;
	size_t outOffset = 0;
	for (size_t i = 0; i < SIZE_OF_HEXGRID; i++) {
		for (size_t j = 0; j < SIZE_OF_HEXGRID; j++) {
			for (size_t k = 0; k < 12; k++) {
				indices[inOffset + k] = singleHexIndices[k] + outOffset;
			}
			outOffset += 6;
			inOffset += 12;
		}
	}

	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_WIREFRAME, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_WIREFRAME, wresourceFilenameFS, resourceFilenameFS))
	{
		Log << "ERROR: Unable to find one or more resources: " << endl;
		Log << "  " << VERTEX_SHADER_WIREFRAME << endl;
		Log << "  " << FRAGMENT_SHADER_WIREFRAME << endl;
		return false;
	}

	//std::wstring wresourceFilenameVS2;
	//std::wstring wresourceFilenameFS2;
	//std::string resourceFilenameVS2;
	//std::string resourceFilenameFS2;
	//
	//// If resource files cannot be found, return
	//if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_WIREFRAME, wresourceFilenameVS2, resourceFilenameVS2) ||
	//	!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_WIREFRAME, wresourceFilenameFS2, resourceFilenameFS2))
	//{
	//	Log << "ERROR: Unable to find one or more resources: " << endl;
	//	Log << "  " << VERTEX_SHADER_TEXTURED_3D_OBJECT << endl;
	//	Log << "  " << FRAGMENT_SHADER_TEXTURED_3D_OBJECT << endl;
	//	return false;
	//}

	openGLRenderer->createShaderProgram(
		&gridShaderProgramID, 
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str());

	openGLRenderer->allocateGraphicsMemoryForObject(
		&gridShaderProgramID,
		&gridVAOID, verticesRaw,
		SIZE_OF_HEXGRID * SIZE_OF_HEXGRID * 6,
		indices, getNumIndices());
	
	//openGLRenderer->allocateGraphicsMemoryForObject(
	//	&gridVAOIDTexture,
	//	&gridVAOID, verticesRaw,
	//	SIZE_OF_HEXGRID * SIZE_OF_HEXGRID * 6,
	//	indices, getNumIndices());

	delete[] verticesRaw;
	delete[] indices;

	return true;
}

unsigned int* CHexGrid::getShaderProgramId()
{
	return &gridShaderProgramID;
}

unsigned int * CHexGrid::getVAOID()
{
	return &gridVAOID;
}

unsigned int * CHexGrid::getShaderProgramIdTexture()
{
	return &gridTextureProgramID;
}

unsigned int * CHexGrid::getVAOIDTexture()
{
	return &gridVAOIDTexture;
}

int CHexGrid::getNumIndices()
{
	return 4 * SIZE_OF_HEXGRID * SIZE_OF_HEXGRID;
}

CVector3 CHexGrid::getCellPointInfo(int x, int y, int point)
{
	return m_hexLayout[x][y]->getPoint(point);
}

CVector3 CHexGrid::getCenter(int i, int j)
{
	return m_hexLayout[i][j]->getCenter();
}

void CHexGrid::createTextureWorld(vector<unsigned int>* textureID)
{
	for (size_t i = 0; i < 100; i++) {
		for (size_t j = 0; j < 100; j++) {
			if (i > SIZE_OF_HEXGRID / 2 && j > SIZE_OF_HEXGRID / 2)
				m_hexLayout[i][j]->setTextureID(textureID->at(0));
			if (i > SIZE_OF_HEXGRID / 2 && j < SIZE_OF_HEXGRID / 2)
				m_hexLayout[i][j]->setTextureID(textureID->at(1));
			if (i < SIZE_OF_HEXGRID / 2 && j > SIZE_OF_HEXGRID / 2)
				m_hexLayout[i][j]->setTextureID(textureID->at(2));
			if (i < SIZE_OF_HEXGRID / 2 && j < SIZE_OF_HEXGRID / 2)
				m_hexLayout[i][j]->setTextureID(textureID->at(3));
		}
		
	}
}
