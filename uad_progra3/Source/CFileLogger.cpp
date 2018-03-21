#include "../Include/CFileLogger.h"

CFileLogger* CFileLogger::_instance = 0;

CFileLogger::CFileLogger()
{
	std::string fileName = getFileName();
	std::string dir;
	_ost = &_file;

	if (getenv("PROGRA_TEMP"))
		dir = getenv("PROGRA_TEMP");
	else if (getenv("TEMP"))
		dir = getenv("TEMP");
	else throw new std::runtime_error ("Ninguna variable de ambiente encontrada ");
	dir += "\\";
	dir += fileName;
	//std::cout << dir << std::endl;
	_file.open(dir, std::ios::out);
	_file << fileName << std::endl;
}

CFileLogger::~CFileLogger()
{
	_file.close();
}

std::string CFileLogger::getFileName()
{
	char str[20];
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(str, 100, "%d_%m_%y_%H-%M-%S", &timeinfo);

	char filename[MAX_PATH];
	DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH);
	if (!size)
		std::cout << "Could not fine EXE file name.\n";

	char *nextToken = NULL;
	char *token = NULL;
	char *tokenSaver = NULL;

	const char *delimiter = "\\";
	const char *delimiter2 = ".";

	token = strtok_s(filename, delimiter, &nextToken);
	while (token) {
		tokenSaver = token;
		token = strtok_s(NULL, delimiter, &nextToken);
	}
	token = strtok_s(tokenSaver, delimiter2, &nextToken);

	std::string str1 (token);
	str1 += "_";
	str1 += str;
	str1 += ".log";

	return str1;
}

CFileLogger * CFileLogger::getFileLogger()
{
	if (_instance == 0){
		_instance = new CFileLogger();
	}
	return _instance;
}

/*
void CFileLogger::Log(const char* toPrint)
{
	_file << "\n" << toPrint;
}
*/
