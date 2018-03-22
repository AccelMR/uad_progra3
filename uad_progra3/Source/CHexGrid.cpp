#include "..\Include\CHexGrid.h"
#include "..\Include\CWideStringHelper.h"


CHexGrid::CHexGrid() :
	gridShaderProgramID(0),
	gridVAOID(0)
{
}

CHexGrid::~CHexGrid()
{
	delete[] m_hexLayout;
}

bool CHexGrid::Inicialize(COpenGLRenderer *openGLRenderer)
{
	// Temp array that saves XYZ of just one hexcell
	float v[6*3];

	// Array that saves XYZ of each hexcell
	float *verticesRaw = new float[sizeof(float)*(SIZE_OF_HEXGRID *SIZE_OF_HEXGRID * 6 * 3)];
	
	// Indices that indicates the order of triangles inner the hex
	unsigned short *indices = new unsigned short[3 * 4 * SIZE_OF_HEXGRID * SIZE_OF_HEXGRID];

	//float vertices[] = { .5,0,-1,1,0,0,.5,0,1,-.5,0,1,-1,0,0,-.5,0,-1 };

	// HexLayout, if center is even then it adds 1/2 to X(i) else (odd) it adds 1/2 to X(i) and 1 to Y(j)
	// Then it creates the VerticesRaw array. It has XYZ of each vertex
	size_t offset = 0;
	for (int i  = 0; i  < SIZE_OF_HEXGRID; i++) {
		for (int j = 0; j < SIZE_OF_HEXGRID; j++) {
			float x = (float)i * 1.5f;

			if (i == 0) {
				if (j == 0) {
					m_hexLayout[i][j] = new CHexGridCell(x, (float)j);
				}
				else { 
					m_hexLayout[i][j] = new CHexGridCell(x, (float)j + j);
				}
				
			}

			else if (i % 2 != 0) {
				if (j == 0) { 
					m_hexLayout[i][j] = new CHexGridCell(x, (float)j + 1.0f);
				}
				else  {
					m_hexLayout[i][j] = new CHexGridCell(x, (float)j + j + 1.0f);
				}
			}

			else if (i % 2 == 0) {
				if (j == 0) { 
					m_hexLayout[i][j] = new CHexGridCell(x, (float)j);
				}
				else  {
					m_hexLayout[i][j] = new CHexGridCell(x, (float)j + j);
				}
			}


			m_hexLayout[i][j]->getVertices(v);
			memcpy(&verticesRaw[offset], v, sizeof (float) * (6 * 3));
			offset += 6 * 3;
		}
	}

	for (size_t i = 0; i < 200; i++)
	{
	//	if (i>17)
	//	{
	//		for (size_t j = 0; j < 3 ; j++)
	//		{
	//			std::cout << j + 1 << ":\t" << verticesRaw[i * 3 + j] << "\t\t";
	//
	//		}
	//	}
	//	std::cout << std::endl;
	}

	unsigned short singleHexIndices[] = {	1,2,0,
											0,2,3,
											3,4,0,
											0,4,5 };

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
	return 12 * SIZE_OF_HEXGRID * SIZE_OF_HEXGRID;
}
