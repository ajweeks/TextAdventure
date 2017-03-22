#pragma once

#include <string>
#include <algorithm>

#define WINDOWS true

void ToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

void RemoveWhiteSpaces(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), iswspace), str.end());
}

void RemoveLeadingAndTrailingWhiteSpaces(std::string& str)
{
	if (str.empty()) return;

	if (iswspace(str.at(0))) str.erase(str.begin(), str.begin() + 1);
	if (iswspace(str.at(str.length() - 1))) str.erase(str.end() - 1, str.end());
}

void ClearConsole()
{
#if WINDOWS
	system("CLS");
#elif MAC
	system("CLEAR");
#endif
}
