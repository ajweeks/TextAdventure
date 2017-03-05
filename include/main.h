#pragma once

#include "enums.h"

#include <vector>
#include <string>

struct Action
{
	Action_Type type;
	std::vector<std::string> names;
};
std::vector<Action> gActions;

struct Item
{
	std::vector<std::string> names;
	std::vector<Action> actions;
};
std::ostream& operator<<(std::ostream& stream, const Item& item)
{
	stream << item.names[0];
	return stream;
}

struct Area
{
	std::string name;
	std::vector<Item> items;
	std::vector<std::pair<Area*, Direction>> neighbors;

	void Describe() const;
	void DescribeItems()const;
	void DescribeNeighbors() const;
};
std::ostream& operator<<(std::ostream& stream, const Area& area)
{
	stream << area.name;
	return stream;
}

struct Player
{
	std::vector<Item> inventory;
};

struct World
{
	Area* currentArea;
	std::vector<Area> areas;

	void Initialize();
};

struct ApplyInputResult
{
	bool success;
	std::string extraInfo;
};

struct ParsedInput
{
	Action_Type actionType;
	std::string actionString;
	std::string extraWords;
	std::string remainingString;
};

void MapActions();
void PlayGame();
void PrintErrorMessage(const ParsedInput& parsedInput, const ApplyInputResult& inputResult);
ApplyInputResult ApplyInput(World& world, const ParsedInput& parsedInput);
ParsedInput ParseInput(const std::string& input);
std::string RemoveExtraWordsFromRemainingInput(std::string& remainingString);
