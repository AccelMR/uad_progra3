#include "../Include/C3DModel_STL.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Include/CLogger.h"

using namespace std;



C3DModel_STL::C3DModel_STL()
	:m_vertices(nullptr),
	m_normals(nullptr),
	m_UVCoords(nullptr)
{
	Log << "Contructor: 3DModel_STL()" << endl;
}

C3DModel_STL::~C3DModel_STL()
{
	reset();
}

bool C3DModel_STL::loadFromFile(const char * const filename)
{
	bool readFileOk = false;

	// Free any previous resources
	reset();

	// First pass is to count the number of vertices, normals, UVs, faces
	readFileOk = readFile(filename);

	// Display count
	Log << "Finished reading 3D model" << endl;
	Log << "Vertices: " << m_numVertices << endl;
	Log << "Normals: " << m_numNormals << endl;
	Log << "UVCoords: " << m_numUVCoords << endl;
	Log << "Faces: " << m_numFaces << endl;


	if (readFileOk)
	{
		// Check for MAX number of faces
		if (m_numVertices >= 65535 || m_numNormals >= 65535 || m_numUVCoords >= 65535)
		{
			Log << "Error: object cannot have more than 65535 vertices" << endl;
			Log << "Object attempted to load has: " << m_numVertices << " vertices" << endl;
			return false;
		}

		if (readFileOk)
		{
			m_Initialized = true;
		}
	}
	else
	{
		Log << "Error ocurred while reading 3D model." << endl;
	}

	return readFileOk;
}

void C3DModel_STL::reset()
{
	if (m_vertexIndices != NULL)
	{
		Log << "deleting vertex indices" << endl;
		delete[] m_vertexIndices;
		m_vertexIndices = NULL;
	}
	if (m_normalIndices != NULL)
	{
		Log << "deleting normal indices" << endl;
		delete[] m_normalIndices;
		m_normalIndices = NULL;
	}
	if (m_UVindices != NULL)
	{
		Log << "deleting UV indices" << endl;
		delete[] m_UVindices;
		m_UVindices = NULL;
	}
	if (m_vertices != NULL)
	{
		Log << "deleting vertices" << endl;
		delete[] m_vertices;
		m_vertices = NULL;
	}
	if (m_verticesRaw != NULL)
	{
		Log << "deleting vertices (float)" << endl;
		delete[] m_verticesRaw;
		m_verticesRaw = NULL;
	}
	if (m_normals != NULL)
	{
		Log << "deleting normals" << endl;
		delete[] m_normals;
		m_normals = NULL;
	}
	if (m_normalsRaw != NULL)
	{
		Log << "deleting normals (float)" << endl;
		delete[] m_normalsRaw;
		m_normalsRaw = NULL;
	}
	if (m_UVCoords != NULL)
	{
		Log << "deleting UV coords" << endl;
		delete[] m_UVCoords;
		m_UVCoords = NULL;
	}
	if (m_uvCoordsRaw != NULL)
	{
		Log << "deleting uvCoords (float)" << endl;
		delete[] m_uvCoordsRaw;
		m_uvCoordsRaw = NULL;
	}

	m_numVertices = 0;
	m_numNormals = 0;
	m_numUVCoords = 0;
	m_numFaces = 0;

	m_Initialized = false;

	m_currentVertex = 0;
	m_currentNormal = 0;
	m_currentUV = 0;
	m_currentFace = 0;

	m_graphicsMemoryObjectId = 0;
	m_shaderProgramId = 0;
}

bool C3DModel_STL::readFile(const char * const filename)
{
	// STL file comes with a Attribute byte count. 2 bytes size.
	short int sintPos;
	short Atribute;

	fopen_s(&_objFileName, filename, "rb");

	if (_objFileName != nullptr) {
		for (int i = 0; i < Header_Size; i++) {
			fread(&sintPos, sizeof(char), 1, _objFileName);
			headerArr[i] = sintPos;
		}

		fread(&m_numFaces, sizeof(unsigned long), 1, _objFileName);
		int triangles = m_numFaces;
		//cout << "Numero de caras : " << m_numFaces << endl;

		//Because STL is used for 3D printing, it doesn't have any UVCoords. So I set same # of vertex
		m_numNormals = m_numFaces;
		m_numVertices = m_numFaces * 3;
		m_numUVCoords = m_numFaces * 3;

		m_vertices = new CVector3[m_numVertices];//3 
		m_normals = new CVector3[m_numFaces];//1 
		m_UVCoords = new CVector3[m_numUVCoords];//3 

		m_verticesRaw = new float[m_numVertices * 3]; //9
		m_normalsRaw = new float[m_numFaces * 3]; //3
		m_uvCoordsRaw = new float[m_numUVCoords * 3]; //9

		m_vertexIndices = new unsigned short[m_numFaces * 3];
		m_normalIndices = new unsigned short[m_numFaces * 3];
		m_UVindices = new unsigned short[m_numFaces * 3];
		

		float tempGetVal[3];
		int posToPut = 0;

		// STL struct is easy. First 80 characters are header then 1 long int for num of faces
		// Now for N-faces there's one normal, and 3 vertex.
		for (int i = 0; i < triangles; i++) {

			for (int j = 0; j < 3; j++) {
				fread(&tempGetVal[j], sizeof(float), 1,(FILE*)_objFileName);
				m_normalsRaw[i * 3 + j] = tempGetVal[j];
				m_normalIndices[i * 3 + j] = i;

			}
			m_normals[i].setValues(tempGetVal[0], tempGetVal[1], tempGetVal[2]);
			/*for (int o = 0; o < 3; o++) {
				cout << m_normals->getX() << "  " << m_normals->getY() << "  " << m_normals->getZ() <<  endl;
			}*/

			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					fread(&tempGetVal[j], sizeof(float), 1, (FILE*)_objFileName);
					m_verticesRaw[posToPut * 3 + k] = tempGetVal[j];
					m_uvCoordsRaw[posToPut * 3 + k] = 0.0;
				}
				m_vertices[posToPut].setValues(tempGetVal[0], tempGetVal[1], tempGetVal[2]);
				m_UVCoords[posToPut].setValues(tempGetVal[0], tempGetVal[1], tempGetVal[2]);
				/*for (int o = 0; o < 3; o++) {
					cout << " \n "<< m_vertices->getX() << "  " << m_vertices->getY() << "  " << m_vertices->getZ() << endl;
				}*/
				posToPut++;
					
				m_vertexIndices[i * 3 + j] = i * 3 + j;
				m_UVindices[i * 3 + j] = i * 3 + j;
			}

			fread(&Atribute, sizeof(short), 1, _objFileName);
			//cout << "Atribbute  :" << Atribute << endl << endl;
		}
	}
	return true;
}