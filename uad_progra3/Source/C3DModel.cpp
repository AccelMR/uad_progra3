#include "../stdafx.h"

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <wchar.h>
#include "..\C3DModel_Obj.h"

using namespace std;

#include "../Include/C3DModel.h"

/* */
C3DModel::C3DModel()
	: m_vertexIndices(NULL),
	m_normalIndices(NULL),
	m_UVindices(NULL),
	m_verticesRaw(NULL),
	m_normalsRaw(NULL),
	m_uvCoordsRaw(NULL),
	m_Initialized(false),
	m_numVertices(0), 
	m_numNormals(0), 
	m_numUVCoords(0), 
	m_numFaces(0),
	m_currentVertex(0),
	m_currentNormal(0),
	m_currentUV(0),
	m_currentFace(0),
	m_graphicsMemoryObjectId(0),
	m_shaderProgramId(0)
{
	cout << "Constructor: C3DModel()" << endl;
}

/* */
C3DModel::~C3DModel()
{
	cout << "Destructor: C3DModel()" << endl;
}

C3DModel * C3DModel::load(const wchar_t * filename)
{
	C3DModel* newObject = nullptr;
	//...
	wchar_t *file_cpy = new wchar_t[wcslen(filename) + 1];
	wcsncpy(file_cpy, (wchar_t*)filename, (int)wcslen(filename) + 1);

	wchar_t* buffer;
	const wchar_t* token = wcstok_s((wchar_t*)file_cpy, L".", &buffer);

	while (token != nullptr) {
		if (wcscmp(L"obj",token) == 0){
			newObject = new C3DModel_Obj();

			if (filename == nullptr) {
				cout << "Error al convertir, puntero nulo." << endl;
				return 0;
			}

			// Toma el tamaño necesario para crear el arreglo de caracteres.  wcslen documentación  https://msdn.microsoft.com/en-us/library/78zh94ax.aspx?f=255&MSPPError=-2147217396
			int size_needed = WideCharToMultiByte(CP_UTF8, 0, filename, (int)wcslen(filename), NULL, 0, NULL, NULL);

			//Genera un string del tamaño especificado por usuario y lo llena con caracteres del alfabeto    http://www.cplusplus.com/reference/cstdlib/malloc/ 
			//char* strTo = (char*)malloc((size_needed + 1) * sizeof(char));
			char* strTo = new char[size_needed + 1];

			// Convierte la linea de caracteres y lo almacena en la hecha previamente 
			WideCharToMultiByte(CP_UTF8, 0, filename, (int)wcslen(filename), strTo, size_needed, NULL, NULL);
			strTo[size_needed] = '\0';

			newObject->loadFromFile(strTo);
			delete[] strTo;
			return newObject;
		}
		 else if (wcscmp(L"stl", token) == 0) {
			newObject = new C3DModel_Obj();

			if (filename == nullptr) {
				cout << "Error al convertir, puntero nulo." << endl;
				return 0;
			}

			// Toma el tamaño necesario para crear el arreglo de caracteres.  wcslen documentación  https://msdn.microsoft.com/en-us/library/78zh94ax.aspx?f=255&MSPPError=-2147217396
			int size_needed = WideCharToMultiByte(CP_UTF8, 0, filename, (int)wcslen(filename), NULL, 0, NULL, NULL);

			//Genera un string del tamaño especificado por usuario y lo llena con caracteres del alfabeto    http://www.cplusplus.com/reference/cstdlib/malloc/ 
			char* strTo = (char*)malloc((size_needed + 1) * sizeof(char));

			// Convierte la linea de caracteres y lo almacena en la hecha previamente 
			WideCharToMultiByte(CP_UTF8, 0, filename, (int)wcslen(filename), strTo, size_needed, NULL, NULL);
			strTo[size_needed] = '\0';

			newObject->loadFromFile(strTo);
			return newObject;
		}

			token = wcstok_s(nullptr, L"\\", &buffer);
	}
	delete[] file_cpy;
	return nullptr;
}