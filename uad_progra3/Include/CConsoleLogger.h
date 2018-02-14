#pragma once
#include "../Include/CLogger.h"

class CConsoleLogger :
	public CLogger
{
private:
	CConsoleLogger();

	static CConsoleLogger* _instance;

public:
	~CConsoleLogger();
	static CConsoleLogger* getConsoleLogger();
};

CConsoleLogger* CConsoleLogger::_instance = nullptr;
