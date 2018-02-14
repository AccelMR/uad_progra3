#pragma once
#include "../Include/CLogger.h"

class CFileLogger :
	public CLogger
{
private:
	CFileLogger();
	static CFileLogger* _instance;

public:
	~CFileLogger();
	static CFileLogger* getFileLogger();
};

CFileLogger* CFileLogger::_instance = nullptr;

