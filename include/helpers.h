#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#define WINDOWS true

void ToLower(std::string& str);
void RemoveWhiteSpaces(std::string& str);
void RemoveLeadingAndTrailingWhiteSpaces(std::string& str);
void RemoveCharFromString(std::string& str, char character);

std::vector<std::string> Split(const std::string& values, char delim = '\n');

template<class T>
bool ContainsDuplicates(const std::vector<T>& vec);

template<class T>
bool Contains(const std::vector<T>& vec, const T& t);

void ClearConsole();