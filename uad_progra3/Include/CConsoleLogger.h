#pragma once
#include "../Include/CLogger.h"

#include <iostream>

class CConsoleLogger :
	public CLogger
{
private:
	static CConsoleLogger* _instance;
	
protected:
	CConsoleLogger();

public:
	~CConsoleLogger();

	static CConsoleLogger* getConsoleLogger();

	//void Log(const char* toPrint);
};
