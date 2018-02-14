#include "../Include/CConsoleLogger.h"



CConsoleLogger::CConsoleLogger()
{
}


CConsoleLogger::~CConsoleLogger()
{
}

CConsoleLogger * CConsoleLogger::getConsoleLogger()
{
	if (_instance == nullptr) {
		_instance = new CConsoleLogger();
	}
	return _instance;
}
