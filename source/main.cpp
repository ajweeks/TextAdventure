
// 2DAE1
// AJ Weeks

#include "main.h"
#include "enums.h"
#include "helpers.h"
#include "MainVisitor.h"

#include <antlr4-runtime.h>
#include "textworldLexer.h"
#include "textworldParser.h"
#include "textworldBaseListener.h"
#include "textworldBaseVisitor.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

#include <Windows.h>

using namespace antlr4;

int main(int argc, const char* argv[])
{
	std::ifstream stream;
	stream.open(argv[1]);
	if (stream.is_open())
	{
		ANTLRInputStream input(stream);
		textworldLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		textworldParser parser(&tokens);

		tree::ParseTree* tree = parser.world();

		textworldVisitor* visitor = new MainVisitor();

		visitor->visit(tree);

		MapActions();

		std::string response;
		do
		{
			PlayGame();
			std::cout << "Play again? (y/n)" << std::endl;
		} while (response.at(0) == 'y' || response.at(0) == 'Y');

		std::cout << "Enter any character to exit..." << std::endl;
		std::string s;
		std::getline(std::cin, s);
	}
}

void Area::Describe() const
{
	std::cout << std::endl << "You are in " << name << std::endl;

	DescribeItems();
	DescribeNeighbors();

	std::cout << std::endl;
}

void Area::DescribeItems()const
{
	if (items.empty())
	{
		std::cout << "There is nothing in this area" << std::endl;
		return;
	}
	std::cout << "In this area you find: " << std::endl;
	for (size_t i = 0; i < items.size(); i++)
	{
		if (i > 0) std::cout << ", ";
		std::cout << items[i];
	}
	std::cout << std::endl;
}

void Area::DescribeNeighbors() const
{
	assert(!neighbors.empty());

	std::cout << "You can go to: " << std::endl;
	for (size_t i = 0; i < neighbors.size(); i++)
	{
		if (i > 0) std::cout << ", ";
		std::cout << *(neighbors[i].first) << " (" << DirectionToShortString(neighbors[i].second) << ")";
	}
	std::cout << std::endl;
}

// TODO: Write tests to prevent invalid worlds from going under the radar
void World::Initialize()
{
	Action aThrow = { Action_Type::THROW,{ "throw", "huck" } };
	Action aInspect = { Action_Type::INSPECT,{ "inspect", "examine", "look at" } };
	Action aTrade = { Action_Type::TRADE,{ "trade", "swap" } };
	Action aEat = { Action_Type::EAT,{ "eat", "consume", "gobble down" } };
	Action aRead = { Action_Type::READ,{ "read", "study" } };

	Item iRock = { { "rock", "stone", "boulder" },{ aInspect, aTrade, aThrow }, "A large, chunky rock" };
	Item iApple = { { "apple" },{ aInspect, aTrade, aThrow, aEat }, "A slightly-moudly looking red apple" };
	Item iBook = { { "book" },{ aInspect, aTrade, aThrow, aRead }, "Looks like some kind of bible written in a cryillic language" };

	Area area1 = {};
	area1.name = "area1";
	area1.items = { iRock, iApple };
	areas.push_back(area1);

	Area area2 = {};
	area2.name = "area2";
	area2.items = { iApple, iApple, iApple };
	areas.push_back(area2);

	Area area3 = {};
	area3.name = "area3";
	area3.items = { iBook };
	areas.push_back(area3);

	Area area4 = {};
	area4.name = "area4";
	area4.items = { iBook, iBook };
	areas.push_back(area4);

	areas[0].neighbors = {
		{ &areas[1], Direction::SOUTH },
		{ &areas[2], Direction::SOUTHEAST }
	};
	areas[1].neighbors = {
		{ &areas[0], Direction::NORTH },
		{ &areas[2], Direction::NORTHEAST }
	};
	areas[2].neighbors = {
		{ &areas[0], Direction::NORTHWEST },
		{ &areas[1], Direction::SOUTHWEST },
		{ &areas[3], Direction::SOUTH }
	};
	areas[3].neighbors = {
		{ &areas[2], Direction::NORTH }
	};

	currentArea = &areas[0];
}

std::string RemoveExtraWordsFromRemainingInput(std::string& remainingString)
{
	std::string usedExtraWords;
	const std::vector<std::string> extraWords = { "to", "at", "with", "now", "immediately" };
	for (size_t i = 0; i < extraWords.size(); i++)
	{
		size_t t = remainingString.find(extraWords[i]);
		if (t != std::string::npos)
		{
			remainingString.erase(remainingString.begin() + t, remainingString.begin() + t + extraWords[i].length());
			usedExtraWords += extraWords[i];
		}
	}
	return usedExtraWords;
}

ParsedInput ParseInput(const std::string& input)
{
	ParsedInput result = {};
	result.remainingString = "";
	result.actionType = Action_Type::_LAST;

	size_t firstSpace = input.find(' ');
	if (firstSpace == std::string::npos) firstSpace = input.length();
	std::string firstWord = input.substr(0, firstSpace);

	for (size_t i = 0; i < gActions.size(); i++)
	{
		for (size_t j = 0; j < gActions[i].names.size(); j++)
		{
			if (firstWord.compare(gActions[i].names[j]) == 0)
			{
				result.actionString = firstWord;
				result.actionType = gActions[i].type;
				size_t actionInputLen = gActions[i].names[j].length();
				result.remainingString = input.substr(actionInputLen);
				result.extraWords = RemoveExtraWordsFromRemainingInput(result.remainingString);
				RemoveLeadingAndTrailingWhiteSpaces(result.remainingString);
				return result;
			}
		}
	}
	return result;
}

ApplyInputResult ApplyInput(World& world, const ParsedInput& parsedInput)
{
	ApplyInputResult result = {};

	switch (parsedInput.actionType)
	{
	case Action_Type::GO:
	{
		Direction direction = StringToDirection(parsedInput.remainingString);
		if (direction != Direction::_LAST)
		{
			// This is a valid direction, store it in the output object
			result.extraInfo = parsedInput.remainingString;
			for (size_t i = 0; i < world.currentArea->neighbors.size(); i++)
			{
				if (world.currentArea->neighbors[i].second == direction)
				{
					world.currentArea = world.currentArea->neighbors[i].first;
					result.success = true;
					result.describeAreaAgain = true;
					return result;
				}
			}
		}
		else
		{
			for (size_t i = 0; i < world.currentArea->neighbors.size(); i++)
			{
				std::string neighborName = world.currentArea->neighbors[i].first->name;
				std::string noWSInput = parsedInput.remainingString;
				RemoveLeadingAndTrailingWhiteSpaces(noWSInput);
				if (neighborName.compare(noWSInput) == 0)
				{
					world.currentArea = world.currentArea->neighbors[i].first;
					result.success = true;
					result.extraInfo = neighborName;
					result.describeAreaAgain = true;
					return result;
				}
			}
		}
	} break;
	case Action_Type::INVENTORY:
		break;
	case Action_Type::TAKE:
		break;
	case Action_Type::DROP:
		break;
	case Action_Type::EQUIP:
		break;
	case Action_Type::EAT:
	{
		std::string itemName = parsedInput.remainingString;
	} break;
	case Action_Type::TRADE:
		break;
	case Action_Type::GIVE:
		break;
	case Action_Type::SPEAK:
		break;
	case Action_Type::ENTER:
		break;
	case Action_Type::EXIT:
		break;
	case Action_Type::LOOK:
		break;
	case Action_Type::INSPECT:
	{
		std::string itemToBeInspectedName = parsedInput.remainingString;

		for (Item& item : world.currentArea->items)
		{
			if (item.names[0].compare(itemToBeInspectedName) == 0)
			{
				std::string itemDescription = item.description;

				std::cout << itemDescription << std::endl;

				result.success = true;
				result.describeAreaAgain = false;

				return result;
			}
		}
	} break;
	case Action_Type::READ:
		break;
	case Action_Type::ATTACK:
		break;
	case Action_Type::THROW:
		break;
	case Action_Type::YES:
		break;
	case Action_Type::NO:
		break;
	case Action_Type::_LAST:
		break;
	default:
		break;
	}

	result.success = false;
	return result;
}

void PrintInvalidInputMessage(const ParsedInput& parsedInput, const ApplyInputResult& inputResult)
{
	std::string remainingStringNoWS = parsedInput.remainingString;
	RemoveWhiteSpaces(remainingStringNoWS);

	std::string defaultWarningString = "Sorry, you can't " + parsedInput.actionString + " ";
	if (!parsedInput.extraWords.empty()) defaultWarningString += parsedInput.extraWords + " ";
	defaultWarningString += parsedInput.remainingString;

	// TODO: More detailed usage descriptions?
	switch (parsedInput.actionType)
	{
	case Action_Type::GO:
	{
		if (remainingStringNoWS.empty())
		{
			std::cout << "Please specify where you want to go" << std::endl;
		}
		else
		{
			std::cout << defaultWarningString << std::endl;
		}
	} break;
	case Action_Type::TAKE:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::DROP:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::EQUIP:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::EAT:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::TRADE:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::GIVE:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::SPEAK:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::ENTER:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::EXIT:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::LOOK:
		if (remainingStringNoWS.empty())
		{
			std::cout << "Please specify what you want to look at" << std::endl;
		}
		else
		{
			std::cout << defaultWarningString << std::endl;
		}
		break;
	case Action_Type::INSPECT:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::READ:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::ATTACK:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::THROW:
		std::cout << defaultWarningString << std::endl;
		break;
	case Action_Type::COMMANDS:
		std::cout << "The available commands are: " << std::endl;
		std::cout << "GO, HELP, COMMANDS, INVENTORY, TAKE DROP, EQUIP, EAT, TRADE, GIVE,"
			"SPEAK, ENTER, EXIT, LOOK, INSPECT, READ, ATTACK, THROW, YES, NO" << std::endl;
		break;
	case Action_Type::HELP:
		std::cout << "Type \"commands\" to see all available commands" << std::endl;
		break;

	case Action_Type::INVENTORY:
	case Action_Type::YES:
	case Action_Type::NO:
		// No warning message for these commands
		break;

	case Action_Type::_LAST:
	default:
		std::cout << "Sorry, that was invalid input!" << std::endl;
		std::cout << "Type \"help\" or \"?\" for help" << std::endl;
		std::cout << "Type \"commands\" to see all available commands" << std::endl;
		break;
	}

	std::cout << std::endl;
}

void PlayGame()
{
	std::cout << "Welcome to GAME_NAME!" << std::endl;
	std::cout << std::endl;

	World world;
	world.Initialize();

	Player player;

	bool describeArea = true;

	bool playing = true;
	while (playing)
	{
		if (describeArea)
		{
			world.currentArea->Describe();
		}

		ParsedInput parsedInput;
		ApplyInputResult inputResult = {};
		inputResult.success = true; // Don't print the warning the first time through the loop
		inputResult.describeAreaAgain = true;
		do
		{
			if (!inputResult.success)
			{
				PrintInvalidInputMessage(parsedInput, inputResult);
			}

			std::string input;
			std::getline(std::cin, input);
			ToLower(input);
			parsedInput = ParseInput(input);

			inputResult = ApplyInput(world, parsedInput);
		} while (!inputResult.success);


		describeArea = inputResult.describeAreaAgain;

		//ClearConsole();
	}
}

void MapActions()
{
	gActions.resize(int(Action_Type::_LAST));
	gActions[int(Action_Type::GO)] = { Action_Type::GO,{ "go", "move", "walk", "run" } };
	gActions[int(Action_Type::HELP)] = { Action_Type::HELP,{ "help", "?" } };
	gActions[int(Action_Type::COMMANDS)] = { Action_Type::COMMANDS,{ "commands", "verbs", "actions" } };
	gActions[int(Action_Type::INVENTORY)] = { Action_Type::INVENTORY,{ "inventory", "i" } };
	gActions[int(Action_Type::TAKE)] = { Action_Type::TAKE,{ "take", "grab", "pick up" } };
	gActions[int(Action_Type::DROP)] = { Action_Type::DROP,{ "drop", "leave" } };
	gActions[int(Action_Type::EQUIP)] = { Action_Type::EQUIP,{ "equip", "wear" } };
	gActions[int(Action_Type::EAT)] = { Action_Type::EAT,{ "eat", "drink" } };
	gActions[int(Action_Type::TRADE)] = { Action_Type::TRADE,{ "trade", "swap" } };
	gActions[int(Action_Type::GIVE)] = { Action_Type::GIVE,{ "give" } };
	gActions[int(Action_Type::SPEAK)] = { Action_Type::SPEAK,{ "speak", "speak with", "talk", "talk to" } };
	gActions[int(Action_Type::ENTER)] = { Action_Type::ENTER,{ "enter" } };
	gActions[int(Action_Type::EXIT)] = { Action_Type::EXIT,{ "exit" } };
	gActions[int(Action_Type::LOOK)] = { Action_Type::LOOK,{ "look", "look around" } };
	gActions[int(Action_Type::INSPECT)] = { Action_Type::INSPECT,{ "inspect", "examine", "study" } };
	gActions[int(Action_Type::READ)] = { Action_Type::READ,{ "read" } };
	gActions[int(Action_Type::ATTACK)] = { Action_Type::ATTACK,{ "attack", "punch", "kick", "kill", "stab", "shoot" } };
	gActions[int(Action_Type::THROW)] = { Action_Type::THROW,{ "throw", "hurl" } };
	gActions[int(Action_Type::YES)] = { Action_Type::YES,{ "yes", "y" } };
	gActions[int(Action_Type::NO)] = { Action_Type::NO,{ "no", "n" } };
}
