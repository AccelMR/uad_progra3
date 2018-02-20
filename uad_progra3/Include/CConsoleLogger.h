#pragma once
#include "../Include/CLogger.h"

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

	void Log();
};
