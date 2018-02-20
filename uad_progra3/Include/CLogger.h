#pragma once
class CLogger
{
private:
	static CLogger* _instance;

protected:
	CLogger();

public:
	~CLogger();

	static CLogger* getLogger();

	virtual void Log() = 0;

};