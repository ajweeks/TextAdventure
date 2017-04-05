
#include "enums.h"

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
