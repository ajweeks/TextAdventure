
#include "stdafx.h"

#include "IO.h"

#include <iostream>

std::string IO::InputLine()
{
	std::string result;
	std::getline(std::cin, result);
	return result;
}

std::string IO::InputPhrase()
{
	std::string result;
	std::cin >> result;
	return result;
}

void IO::OutputString(const std::string& str, bool newline)
{
	size_t newlineChar = str.find("\\n");
	if (newlineChar != std::string::npos && newlineChar != str.length() - 1)
	{
		auto vec = Split(str, "\\n");
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i] << '\n' << '\n';
		}
	}
	else
	{
		std::cout << str;
		if (newline) std::cout << '\n';
	}
}

void IO::OutputNewLine()
{
	std::cout << '\n';
}
