#include "..\Include\CHexGrid.h"
#include "..\Include\CWideStringHelper.h"


CHexGrid::CHexGrid()
{
}

CHexGrid::~CHexGrid()
{
}

bool CHexGrid::Inicialize(COpenGLRenderer *openGLRenderer)
{
	float v[6*3];
	float *vertices = new float[100 * 100 * 6 * 3];
	unsigned short *indices = new unsigned short[100 * 100 * 4 * 3];

	// Robin
	size_t offset = 0;
	for (int i  = 0; i  < 100; i++) {
		for (int j = 0; j < 100; j++) {

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
			memcpy(&vertices[offset], v, 6 * 3);
			offset += 6 * 3;
		}
	}

	unsigned short singleHexIndices[] = { 0,1,2,0,2,6,6,2,4,6,4,5 };

	size_t inOffset = 0;
	size_t outOffset = 0;
	for (size_t i = 0; i < 100; i++)
		for (size_t j = 0; j < 100; j++)
		{
			for (size_t k = 0; k < 12; k++)
			{
				indices[inOffset + k] = singleHexIndices[k] + outOffset;
				inOffset++;
			}
			outOffset += 6;
		}

	std::wstring wresourceFilenameVS;
	std::wstring wresourceFilenameFS;
	std::string resourceFilenameVS;
	std::string resourceFilenameFS;

	// If resource files cannot be found, return
	if (!CWideStringHelper::GetResourceFullPath(VERTEX_SHADER_TEST_OBJECT, wresourceFilenameVS, resourceFilenameVS) ||
		!CWideStringHelper::GetResourceFullPath(FRAGMENT_SHADER_TEST_OBJECT, wresourceFilenameFS, resourceFilenameFS))
	{
		Log << "ERROR: Unable to find one or more resources: " << endl;
		Log << "  " << VERTEX_SHADER_TEST_OBJECT << endl;
		Log << "  " << FRAGMENT_SHADER_TEST_OBJECT << endl;
		return false;
	}

	openGLRenderer->createShaderProgram(
		&gridShaderProgramID,
		resourceFilenameVS.c_str(),
		resourceFilenameFS.c_str()
	);
	openGLRenderer->allocateGraphicsMemoryForObject(&gridShaderProgramID, &gridVAOID, vertices,
		100 * 100 * 6, indices, 100 * 100 * 4 * 3);

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
	return 4 * 100 * 100;
}
