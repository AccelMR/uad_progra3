#include <cstdlib>
#include "../Include/CLogger.h"
#include "../Include/CFileLogger.h"
#include "../Include/CConsoleLogger.h"


CLogger::CLogger()
{
	if (getenv("PROGRA3_FILE_LOG") != nullptr){
		_instance = CFileLogger::getFileLogger();
	}
	else{
		_instance = CConsoleLogger::getConsoleLogger();
	}
}


CLogger::~CLogger()
{
}

CLogger* CLogger::getLogger()
{
	if (_instance == nullptr){
		_instance = new CLogger();
	}
	return _instance;

}
