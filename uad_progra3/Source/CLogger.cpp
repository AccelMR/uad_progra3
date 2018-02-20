#include <cstdlib>
#include <iostream>
#include "../Include/CLogger.h"
#include "../Include/CFileLogger.h"
#include "../Include/CConsoleLogger.h"

CLogger* CLogger::_instance = 0;

CLogger::CLogger()
{
	//std::cout << "Constructor CLogger()" << std::endl;
}

CLogger::~CLogger()
{
}

CLogger* CLogger::getLogger()
{
	if (getenv("PROGRA3_FILE_LOG")) {
		_instance = CFileLogger::getFileLogger();
	}
	else {
		_instance = CConsoleLogger::getConsoleLogger();
	}
	return _instance;
}