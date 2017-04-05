#pragma once

#include <string>

// Retrieves/outputs strings to/from the user
class IO
{
public:
	//Input
	static std::string InputPhrase();
	static std::string InputLine();

	// Output
	static void OutputString(const std::string& str);
	static void OutputNewLine();

private:
	IO() = delete;
	~IO() = delete;

};
