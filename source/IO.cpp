
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

void IO::OutputString(const std::string& str)
{
	std::cout << str << std::endl;
}

void IO::OutputNewLine()
{
	std::cout << std::endl;
}
