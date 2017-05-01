#pragma once

#include <map>
#include <vector>
#include <array>
#include <string>
#include <map>

// Forward declarations
struct Item;
struct Action;
struct Area;
struct World;
struct Player;
struct ApplyInputResult;
struct ParsedInput;

enum class Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,

	NONE
};

// TODO: Meta program this and the std::map to be generated by the world file
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

struct Globals
{
	// Not "real" items, just definitons
	std::vector<Item*> m_ItemDefinitions; 
	std::array<Action*, (size_t)Action_Type::NONE> m_Actions;
	// All words that we can recognize (items, areas, actions, etc.) Anything not in this list will be ignored
	std::vector<std::string> m_WorldWhitelist; 
};

struct World
{
	Player* m_Player;
	Area* m_CurrentArea;
	std::vector<Area*> m_Areas;
};

struct Area
{
	std::string m_Name;
	std::array<std::pair<Area*, Direction>, 4> m_Neighbors;
	std::string m_Description;
	std::vector<Item*> m_Items;

	void RemoveItem(Item* item);
	void AddItem(Item* item);
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

	std::string DescribeInventory() const;
};

struct ParsedInput
{
	bool m_Success;
	bool m_DescribeAreaAgain;
	std::string m_ErrorMessage;

	// All inputs have an action type
	Action* m_Action;
	std::string m_InputActionString;

	// Most inputs have a noun, but not all (exit doesn't for example)
	std::string m_NounString;

	// The following are only sometimes used
	std::string m_Extra;
	Direction m_Direction = Direction::NONE;
	Area* m_Area;
	Item* m_Item;
	Player* m_Player;
};

std::string DirectionToString(Direction d);
std::string DirectionToShortString(Direction d);
Direction StringToDirection(const std::string& inputString);

void ToLower(std::string& str);
void RemoveWhiteSpaces(std::string& str);
void RemoveLeadingAndTrailingWhiteSpaces(std::string& str);
void RemoveCharFromString(std::string& str, char character);

std::vector<std::string> Split(const std::string& values, char delim = '\n');
std::string Combine(const std::vector<std::string>& vals, char delim = ' ');

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

void ClearConsole();