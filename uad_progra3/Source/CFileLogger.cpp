#include "../Include/CFileLogger.h"

CFileLogger* CFileLogger::_instance = 0;

CFileLogger::CFileLogger()
{
	char* fileName = getFileName();
	std::fstream file(fileName, std::ios::out);
}


CFileLogger::~CFileLogger()
{
}

char * CFileLogger::getFileName()
{
	char str[20];
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(str, 100, "%R%p %F", &timeinfo);

	for (int i = 0; i < 20; i++) {
		if (str[i] == ':')
			str[i] = '_';
	}
	return str;
}

CFileLogger * CFileLogger::getFileLogger()
{
	if (_instance == 0){
		_instance = new CFileLogger();
	}
	return _instance;
}

