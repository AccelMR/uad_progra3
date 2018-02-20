#include "../Include/CConsoleLogger.h"

CConsoleLogger* CConsoleLogger::_instance = nullptr;

CConsoleLogger::CConsoleLogger()
{
}

CConsoleLogger::~CConsoleLogger()
{
}

CConsoleLogger * CConsoleLogger::getConsoleLogger()
{
	if (_instance == 0) {
		_instance = new CConsoleLogger();
	}
	return _instance;
}

void CConsoleLogger::Log(const char* toPrint)
{
	std::cout << toPrint;
}
