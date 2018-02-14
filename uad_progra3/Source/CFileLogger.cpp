#include "../Include/CFileLogger.h"



CFileLogger::CFileLogger()
{
}


CFileLogger::~CFileLogger()
{
}

CFileLogger * CFileLogger::getFileLogger()
{
	if (_instance == nullptr){
		_instance = new CFileLogger();
	}
	return _instance;
}
