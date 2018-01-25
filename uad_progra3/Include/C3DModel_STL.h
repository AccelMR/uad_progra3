#pragma once
#include "../Include/C3DModel.h"


class C3DModel_STL :
	public C3DModel
{
public:
	C3DModel_STL();
	~C3DModel_STL();

	bool loadFromFile();
	void reset();

	bool parseLine(std::string line, bool countOnly, int lineNumber);
	bool readFile(const char * const filename, bool countOnly);
};

