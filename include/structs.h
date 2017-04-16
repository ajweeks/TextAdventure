#pragma once

#include "enums.h"

#include <map>
#include <vector>
#include <array>
#include <string>

// Forward declarations
struct Item;
struct Action;
struct Area;
struct World;
struct Player;

struct World
{
	Player* m_Player;
	Area* m_CurrentArea;
	std::vector<Area*> m_Areas;
	std::vector<Item*> m_Items;
	std::array<Action*, (size_t)Action_Type::NONE> m_Actions;
};

struct Area
{
	std::string m_Name;
	std::array<std::pair<Area*, Direction>, 4> m_Neighbors;
	std::string m_Description;
	std::vector<Item*> m_Items;

	void Describe() const;
	void DescribeItems()const;
	void DescribeNeighbors() const;
};

struct Action
{
	Action_Type m_Type;
	std::vector<std::string> m_Names;
};
std::ostream& operator<<(std::ostream& stream, const Area& area);

struct Item
{
	std::string m_Name;
	std::vector<std::string> m_Descriptions;
	std::vector<Action*> m_Actions;
};
std::ostream& operator<<(std::ostream& stream, const Item& item);

struct Player
{
	std::string m_Name;
	std::vector<Item*> m_Inventory;
};

struct ApplyInputResult
{
	bool m_Success;
	bool m_DescribeAreaAgain;
	std::string m_ExtraInfo;
};

struct ParsedInput
{
	Action_Type m_ActionType;
	std::string m_ActionString;
	std::string m_ExtraWords;
	std::string m_RemainingString;
};
