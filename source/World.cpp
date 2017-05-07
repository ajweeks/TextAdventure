
#include "stdafx.h"

#include "IO.h"
#include "Logger.h"

#include <iostream>
#include <assert.h>
#include <algorithm>
#include <sstream>

void Area::RemoveItem(Item* item)
{
	auto it = std::find(m_Items.begin(), m_Items.end(), item);
	if (it == m_Items.end())
	{
		Logger::LogError("Can't delete item " + item->m_Name + ", it doesn't exist in this area!");
	}
	else
	{ 
		m_Items.erase(it);
	}
}

void Area::AddItem(Item* item)
{
	m_Items.push_back(item);
}

void Area::Describe() const
{
	IO::OutputNewLine();
	IO::OutputString("You are in " + m_Name);

	DescribeArea();
	IO::OutputNewLine();
	
	DescribeItems();
	IO::OutputNewLine();
	
	DescribeNeighbors();
	IO::OutputNewLine();
}

void Area::DescribeArea() const
{
	IO::OutputString(m_Description);
}

void Area::DescribeItems() const
{
	if (m_Items.empty())
	{
		IO::OutputString("There is nothing in this area");
		return;
	}
	IO::OutputString("In this area you find: ");
	for (size_t i = 0; i < m_Items.size(); i++)
	{
		if (i > 0) IO::OutputString(", ", false);
		IO::OutputString(m_Items[i]->m_Name, false);
	}
	IO::OutputNewLine();
}

void Area::DescribeNeighbors() const
{
	assert(!m_Neighbors.empty());

	IO::OutputString("You can go to: ");
	int placeCount = 0;
	for (size_t i = 0; i < m_Neighbors.size(); i++)
	{
		if (m_Neighbors[i].first)
		{
			if (placeCount > 0) IO::OutputString(", ", false);
			IO::OutputString(((m_Neighbors[i].first)->m_Name) + " (" + DirectionToShortString(m_Neighbors[i].second) + ")", false);
			++placeCount;
		}
	}
	IO::OutputNewLine();
}

std::string DirectionToString(Direction d)
{
	switch (d)
	{
	case Direction::NORTH:		return "north";
	case Direction::EAST:		return "east";
	case Direction::SOUTH:		return "south";
	case Direction::WEST:		return "west";
	case Direction::NONE:		return "Invalid direction: NONE enum element";
	default:					return "Unknown direction (index " + std::to_string(int(d)) + ")";
	}
}

std::string DirectionToShortString(Direction d)
{
	switch (d)
	{
	case Direction::NORTH:		return "n";
	case Direction::EAST:		return "e";
	case Direction::SOUTH:		return "s";
	case Direction::WEST:		return "w";
	case Direction::NONE:		return "Invalid Direction: NONE enum element";
	default:					return "Unknown direction (index " + std::to_string(int(d)) + ")";
	}
}

Direction StringToDirection(const std::string& inputString)
{
	std::string str = inputString;
	RemoveWhiteSpaces(str);
	ToLower(str);
	if (str.compare("north") == 0 || str.compare("n") == 0)			return Direction::NORTH;
	if (str.compare("east") == 0 || str.compare("e") == 0)			return Direction::EAST;
	if (str.compare("south") == 0 || str.compare("s") == 0)			return Direction::SOUTH;
	if (str.compare("west") == 0 || str.compare("w") == 0)			return Direction::WEST;
	return Direction::NONE;
}

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

	while (!str.empty() && iswspace(str.at(0))) str.erase(str.begin(), str.begin() + 1);
	while (!str.empty() && iswspace(str.at(str.length() - 1))) str.erase(str.end() - 1, str.end());
}

void RemoveCharFromString(std::string& str, char character)
{
	str.erase(std::remove_if(str.begin(), str.end(), [&character](char c) { return c == character; }), str.end());
}

std::vector<std::string> Split(const std::string& values, std::string delim)
{
	std::vector<std::string> result;
	std::stringstream stream(values);

	while (stream.good())
	{
		std::string line;
		getline(stream, line);

		result.push_back(line);
	}

	int i = 0;
	while (i < result.size())
	{
		size_t find;
		do
		{
			find = result[i].find(delim);

			if (find != std::string::npos)
			{
				result.insert(result.begin() + i + 1, result[i].substr(find + delim.length()));
				result[i] = result[i].substr(0, find);
			}
		} while (find != std::string::npos);
		++i;
	}

	return result;
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

std::string Combine(const std::vector<std::string>& vals, char delim)
{
	if (vals.empty()) return "";

	std::stringstream ss;

	ss << vals[0];
	for (size_t i = 1; i < vals.size(); i++)
	{
		ss << delim << vals[i];
	}

	return ss.str();
}

void ClearConsole()
{
	system("CLS");
}

std::string Player::DescribeInventory() const
{
	std::stringstream ss;
	ss << "Player's inventory contains: " << '\n';
	int placeCount = 0;
	for (size_t i = 0; i < m_Inventory.size(); i++)
	{
		if (placeCount > 0) ss << ", ";
		ss << m_Inventory[i]->m_Name;
		++placeCount;
	}
	ss << '\n';

	return ss.str();
}
