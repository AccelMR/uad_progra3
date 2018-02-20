#pragma once
#include "../Include/CLogger.h"
#include <ctime>
#include <fstream>

class CFileLogger :
	public CLogger
{
private:
	static CFileLogger* _instance;

	char* getFileName();

protected:
	CFileLogger();

public:
	~CFileLogger();

	static CFileLogger* getFileLogger();

	void Log();
};