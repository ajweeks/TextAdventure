#pragma once

#include "helpers.h"

#include <string>
#include <map>

enum class Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,

	NONE
};
std::string DirectionToString(Direction d);
std::string DirectionToShortString(Direction d);
Direction StringToDirection(const std::string& inputString);

// TODO: Meta program this to generate the map automatically
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
	DRINK,
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
	QUIT,

	NONE
};

static std::map<std::string, Action_Type> gStringToActionType = {
	{ "go", Action_Type::GO },
	{ "help", Action_Type::HELP },
	{ "commands", Action_Type::COMMANDS },
	{ "inventory", Action_Type::INVENTORY },
	{ "take", Action_Type::TAKE },
	{ "drop", Action_Type::DROP },
	{ "equip", Action_Type::EQUIP },
	{ "eat", Action_Type::EAT },
	{ "trade", Action_Type::TRADE },
	{ "give", Action_Type::GIVE },
	{ "speak", Action_Type::SPEAK },
	{ "enter", Action_Type::ENTER },
	{ "exit", Action_Type::EXIT },
	{ "look", Action_Type::LOOK },
	{ "inspect", Action_Type::INSPECT },
	{ "read", Action_Type::READ },
	{ "attack",	Action_Type::ATTACK },
	{ "throw", Action_Type::THROW },
	{ "yes", Action_Type::YES },
	{ "no", Action_Type::NO },
	{ "drink", Action_Type::DRINK },
	{ "quit", Action_Type::QUIT },
};
