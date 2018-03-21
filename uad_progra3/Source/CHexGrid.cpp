#include "..\Include\CHexGrid.h"
#include "..\Include\CWideStringHelper.h"


CHexGrid::CHexGrid() :
	gridShaderProgramID(0),
	gridVAOID(0)
{
}

CHexGrid::~CHexGrid()
{
}

bool CHexGrid::Inicialize(COpenGLRenderer *openGLRenderer)
{
	float v[6*3];
	//float *vertices = new float[SIZE_OF_HEXGRID *SIZE_OF_HEXGRID * 6 * 3];
	float vertices[18] = { .5,0,-1,1,0,0,.5,0,1,-.5,0,1,-1,0,0,-.5,0,-1 };
	unsigned short *indices = new unsigned short[SIZE_OF_HEXGRID*SIZE_OF_HEXGRID * 4];

	// Robin
	size_t offset = 0;
	for (int i  = 0; i  < SIZE_OF_HEXGRID; i++) {
		for (int j = 0; j < SIZE_OF_HEXGRID; j++) {

			if (i == 0) {
				if (j == 0) { m_hexLayout[i][j] = new CHexGridCell(i, j); }
				else { m_hexLayout[i][j] = new CHexGridCell(i, j + 1); }
			}

			else if (i % 2 == 0) {
				if (j == 0) { m_hexLayout[i][j] = new CHexGridCell(i + .5, j); }
				else { m_hexLayout[i][j] = new CHexGridCell(i + .5, j + 1); }
			}

			else {
				if (j == 0) { m_hexLayout[i][j] = new CHexGridCell(i + 0.5, j + 1); }
				else { m_hexLayout[i][j] = new CHexGridCell(i + 0.5, j + 2); }
			}

			m_hexLayout[i][j]->getVertices(v);
			//memcpy(&vertices[offset], v, 6 * 3);
			//offset += 6 * 3;
		}
	}

	unsigned short singleHexIndices[] = {	1,2,0,
											0,2,3,
											3,4,0,
											0,4,5 };

	size_t inOffset = 0;
	size_t outOffset = 0;
	for (size_t i = 0; i < SIZE_OF_HEXGRID; i++) {
		for (size_t j = 0; j < SIZE_OF_HEXGRID; j++) {
			for (size_t k = 0; k < SIZE_OF_HEXGRID; k++) {
				indices[inOffset + k] = singleHexIndices[k] + outOffset;
				inOffset++;
			}
			outOffset += 6;
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
		&gridVAOID, vertices,
		SIZE_OF_HEXGRID * SIZE_OF_HEXGRID * 6,
		singleHexIndices, SIZE_OF_HEXGRID * SIZE_OF_HEXGRID * 4 * 3);

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

size_t CHexGrid::getNumFaces()
{
	return 4 * 5 * 5;
}
