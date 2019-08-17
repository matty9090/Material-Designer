#pragma once

#include <map>
#include <string>

class FLog
{
public:
	enum ELogType { Verbose, Info, Warning, Error };

	static FLog& Get()
	{
		static FLog instance;
		return instance;
	}

	FLog(FLog const&) = delete;
	void operator=(FLog const&) = delete;

	void Log(std::string msg, ELogType logLevel = Info);

private:
	FLog() {}

	std::map<ELogType, std::string> LogTypes = {
		{ Verbose, "Verbose"},
		{ Info, "Info"},
		{ Warning, "Warning"},
		{ Error, "Error"}
	};
};
