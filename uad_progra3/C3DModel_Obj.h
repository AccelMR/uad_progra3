#pragma once
#include "c:\Users\accel\Git\uad_progra3\uad_progra3\Include\C3DModel.h"

class C3DModel_Obj :
	public C3DModel
{
private:

	CVector3 * m_vertices;                              // Dynamically-allocated array of vertices
	CVector3 *m_normals;                               // Dynamically-allocated array of normals
	CVector3 *m_UVCoords;                             // Dynamically-allocated array of UV coords

	void reset();

public:
	C3DModel_Obj();
	~C3DModel_Obj();

	bool loadFromFile (const char * const filename);
	bool parseLine(std::string line, bool countOnly, int lineNumber);
	bool readFile(const char * const filename, bool countOnly);
};