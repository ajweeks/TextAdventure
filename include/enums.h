#pragma once

#include "helpers.h"

#include <string>

enum class Direction
{
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST,

	_LAST
};
std::string DirectionToString(Direction d)
{
	switch (d)
	{
	case Direction::NORTH:		return "north";
	case Direction::NORTHEAST:	return "northeast";
	case Direction::EAST:		return "east";
	case Direction::SOUTHEAST:	return "southeast";
	case Direction::SOUTH:		return "south";
	case Direction::SOUTHWEST:	return "southwest";
	case Direction::WEST:		return "west";
	case Direction::NORTHWEST:	return "northwest";
	case Direction::_LAST:		return "Invalid direction: _LAST enum element";
	default:					return "Unknown direction (index " + std::to_string(int(d)) + ")";
	}
}
std::string DirectionToShortString(Direction d)
{
	switch (d)
	{
	case Direction::NORTH:		return "n";
	case Direction::NORTHEAST:	return "ne";
	case Direction::EAST:		return "e";
	case Direction::SOUTHEAST:	return "se";
	case Direction::SOUTH:		return "s";
	case Direction::SOUTHWEST:	return "sw";
	case Direction::WEST:		return "w";
	case Direction::NORTHWEST:	return "nw";
	case Direction::_LAST:		return "Invalid Direction: Last enum element";
	default:					return "Unknown direction (index " + std::to_string(int(d)) + ")";
	}
}

Direction StringToDirection(const std::string& inputString)
{
	std::string str = inputString;
	RemoveWhiteSpaces(str);
	ToLower(str);
	if (str.compare("north") == 0 || str.compare("n") == 0)			return Direction::NORTH;
	if (str.compare("northeast") == 0 || str.compare("ne") == 0)	return Direction::NORTHEAST;
	if (str.compare("east") == 0 || str.compare("e") == 0)			return Direction::EAST;
	if (str.compare("southeast") == 0 || str.compare("se") == 0)	return Direction::SOUTHEAST;
	if (str.compare("south") == 0 || str.compare("s") == 0)			return Direction::SOUTH;
	if (str.compare("southwest") == 0 || str.compare("sw") == 0)	return Direction::SOUTHWEST;
	if (str.compare("west") == 0 || str.compare("w") == 0)			return Direction::WEST;
	if (str.compare("northwest") == 0 || str.compare("nw") == 0)	return Direction::NORTHWEST;
	return Direction::_LAST;
}

enum class Action_Type
{
	GO,
	HELP,
	COMMANDS,
	INVENTORY,
	TAKE,
	DROP,
	EQUIP,
	EAT,
	TRADE,
	GIVE,
	SPEAK,
	ENTER,
	EXIT,
	LOOK,
	INSPECT,
	READ,
	ATTACK,
	THROW,
	YES,
	NO,

	_LAST
};
