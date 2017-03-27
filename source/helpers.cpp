
#include "helpers.h"

void ToLower(std::string & str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

void RemoveWhiteSpaces(std::string & str)
{
	str.erase(std::remove_if(str.begin(), str.end(), iswspace), str.end());
}

void RemoveLeadingAndTrailingWhiteSpaces(std::string& str)
{
	if (str.empty()) return;

	if (iswspace(str.at(0))) str.erase(str.begin(), str.begin() + 1);
	if (iswspace(str.at(str.length() - 1))) str.erase(str.end() - 1, str.end());
}

void RemoveCharFromString(std::string& str, char character)
{
	str.erase(std::remove_if(str.begin(), str.end(), [&character](char c) { return c == character; }), str.end());
}

std::vector<std::string> Split(const std::string& values, char delim)
{
	std::vector<std::string> result;
	std::stringstream valuesStream(values);

	while (valuesStream.good())
	{
		std::string line;
		getline(valuesStream, line, delim);
		if (line.length() > 0)
		{
			result.push_back(line);
		}
	}

	return result;
}

template<class T>
bool ContainsDuplicates(const std::vector<T>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		for (size_t j = i + 1; j < vec.size(); j++)
		{
			if (vec[i] == vec[j]) return true;
		}
	}
	return false;
}
template<class T>
bool Contains(const std::vector<T>& vec, const T& t)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == t) return true;
	}
	return false;
}

void ClearConsole()
{
#if WINDOWS
	system("CLS");
#elif MAC
	system("CLEAR");
#endif
}
