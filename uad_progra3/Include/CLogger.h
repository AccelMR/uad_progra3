#pragma once
#include <iostream>

#define Log CLogger::getLogger()->Out()

class CLogger
{
private:
	static CLogger* _instance;


protected:
	CLogger();

	std::ostream* _ost;

public:
	virtual ~CLogger();

	static CLogger* getLogger();

	//virtual void Log(const char* toPrint) = 0;
	std::ostream& const Out() { return *_ost; }

};