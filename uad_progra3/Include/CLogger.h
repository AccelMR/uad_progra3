#pragma once
class CLogger
{
private:
	static CLogger* _instance;

protected:
	CLogger();

public:
	virtual ~CLogger();

	static CLogger* getLogger();

	virtual void Log(const char* toPrint) = 0;

};