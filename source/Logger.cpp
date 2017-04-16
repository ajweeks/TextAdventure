
#include "Logger.h"

#include <iostream>
#include <assert.h>

void Logger::LogInfo(const std::string& str)
{
	Log(str, Level::INFO);
}

void Logger::LogWarning(const std::string& str)
{
	Log(str, Level::WARNING);
}

void Logger::LogError(const std::string& str, bool crash)
{
	Log(str, Level::ERROR);

	if (crash)
	{
		assert(false);
	}
}

void Logger::Log(const std::string& str, Level logLevel)
{
	std::string prefix;
	
	if (logLevel == Level::INFO) prefix = "[INFO]: ";
	else if (logLevel == Level::ERROR) prefix = "[ERROR]: ";
	else if (logLevel == Level::WARNING) prefix = "[WARNING]: ";

	std::cout << prefix << str << std::endl;
}
