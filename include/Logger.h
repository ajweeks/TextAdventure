#pragma once

#include <string>

// Report errors/warnings/info strings to this for debug output
class Logger
{
public:
	static void LogInfo(const std::string& str);
	static void LogWarning(const std::string& str);
	static void LogError(const std::string& str, bool crash = false);

private:
	enum class Level
	{
		INFO,
		WARNING,
		ERROR
	};

	static void Log(const std::string& str, Level logLevel);

	Logger() = delete;
	~Logger() = delete;

};
