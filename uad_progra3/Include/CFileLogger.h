#pragma once
#include "../Include/CLogger.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>

class CFileLogger :
	public CLogger
{
private:
	static CFileLogger* _instance;

	std::string getFileName();
	std::fstream _file;

protected:
	CFileLogger();

public:
	~CFileLogger();

	static CFileLogger* getFileLogger();

	//void Log(const char* toPrint);
};