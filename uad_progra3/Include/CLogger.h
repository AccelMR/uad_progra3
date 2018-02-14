#pragma once
class CLogger
{
private:
	CLogger();
	static CLogger* _instance;

public:
	~CLogger();

	static CLogger* getLogger();

};

CLogger* CLogger::_instance = nullptr;