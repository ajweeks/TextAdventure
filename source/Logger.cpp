
#include "Logger.h"

#include <iostream>

void Logger::LogInfo(const std::string& str)
{
	Log(str, Level::INFO);
}

void Logger::LogWarning(const std::string& str)
{
	Log(str, Level::WARNING);
}

void Logger::LogError(const std::string& str)
{
	Log(str, Level::ERROR);
}

void Logger::Log(const std::string& str, Level logLevel)
{
	std::string prefix;
	
	if (logLevel == Level::INFO) prefix = "[INFO]: ";
	else if (logLevel == Level::ERROR) prefix = "[ERROR]: ";
	else if (logLevel == Level::WARNING) prefix = "[WARNING]: ";

	std::cout << prefix << str << std::endl;
}
