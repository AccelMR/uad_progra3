#include "..\Include\CHexGrid.h"
#include "..\Include\CWideStringHelper.h"


CHexGrid::CHexGrid() :
	gridShaderProgramID(0),
	gridVAOID(0)
{
	a = (sqrt(3))*size / 2;
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

	// HexLayout, if center is even then it adds 1/2 to X(i) else (odd) it adds 1/2 to X(i) and 1 to Y(j)
	// Then it creates the VerticesRaw array. It has XYZ of each vertex
	size_t offset = 0;
	for (int i  = 0; i  < SIZE_OF_HEXGRID; i++) {
		for (int j = 0; j < SIZE_OF_HEXGRID; j++) {

			// First hexagon is going to be on 0,0 
			if (i == 0)
				if (j == 0)
					m_hexLayout[i][j] = new CHexGridCell(i, j, size, a);
			
			// http://webdevtipstricksandinfo.blogspot.mx/2012/08/creating-hexagonal-grid-for-games-c-java.html
			m_hexLayout[i][j] = new CHexGridCell(j*((3 * size) / 2), (j % 2)*a + 2 * i*a, size, a);

			m_hexLayout[i][j]->getVertices(v);
			memcpy(&verticesRaw[offset], v, sizeof (float) * (6 * 3));
			offset += 6 * 3;
		}
	}


	/*unsigned short singleHexIndices[] = {	1,2,0,
											0,2,3,
											3,4,0,
											0,4,5 };*/


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

	openGLRenderer->createShaderProgram(
		&gridShaderProgramID, 
		resourceFilenameVS.c_str(), 
		resourceFilenameFS.c_str());

	openGLRenderer->allocateGraphicsMemoryForObject(
		&gridShaderProgramID,
		&gridVAOID, verticesRaw,
		SIZE_OF_HEXGRID * SIZE_OF_HEXGRID * 6,
		indices, getNumIndices());

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

int CHexGrid::getNumIndices()
{
	return 4 * SIZE_OF_HEXGRID * SIZE_OF_HEXGRID;
}
