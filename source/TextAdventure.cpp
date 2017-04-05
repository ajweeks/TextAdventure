
// 2DAE1
// AJ Weeks

#include "TextAdventure.h"
#include "enums.h"
#include "helpers.h"
#include "MainVisitor.h"
#include "Logger.h"
#include "IO.h"

#include <antlr4-runtime.h>
#include "textworldLexer.h"
#include "textworldParser.h"
#include "textworldBaseListener.h"
#include "textworldBaseVisitor.h"

#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace antlr4;

TextAdventure::TextAdventure()
{
}

void TextAdventure::Run(const std::string& worldFilePath)
{
	std::ifstream stream;
	stream.open(worldFilePath);
	if (stream.is_open())
	{
		ANTLRInputStream input(stream);
		textworldLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		textworldParser parser(&tokens);

		tree::ParseTree* tree = parser.world();

		m_Visitor = new MainVisitor();

		m_Visitor->visit(tree);
		m_Visitor->PostVisit();

		m_Visitor->m_World->m_Player = new Player();

		std::string response;
		do
		{
			PlayGame();
			IO::OutputString("Play again? (y/n)");
		} while (response.at(0) == 'y' || response.at(0) == 'Y');

		IO::OutputString("Enter any character to exit...");
		std::string s;
		std::getline(std::cin, s);
	}
}

void TextAdventure::PlayGame()
{
	IO::OutputString("Welcome to GAME_NAME!");
	IO::OutputString("");

	Player player;

	bool describeArea = true;

	bool playing = true;
	while (playing)
	{
		if (describeArea)
		{
			m_Visitor->m_World->m_CurrentArea->Describe();
		}

		ParsedInput parsedInput;
		ApplyInputResult inputResult = {};
		inputResult.m_Success = true; // Don't print the warning the first time through the loop
		inputResult.m_DescribeAreaAgain = true;
		do
		{
			if (!inputResult.m_Success)
			{
				PrintInvalidInputMessage(parsedInput, inputResult);
			}

			std::string input;
			std::getline(std::cin, input);
			ToLower(input);
			parsedInput = ParseInput(input);
			
			inputResult = ApplyInput(m_Visitor->m_World, parsedInput);
		} while (!inputResult.m_Success);


		describeArea = inputResult.m_DescribeAreaAgain;

		//ClearConsole();
	}
}

ParsedInput TextAdventure::ParseInput(const std::string& input)
{
	ParsedInput result = {};
	result.m_RemainingString = "";
	result.m_ActionType = Action_Type::NONE;

	size_t firstSpace = input.find(' ');
	if (firstSpace == std::string::npos) firstSpace = input.length();
	const std::string firstWord = input.substr(0, firstSpace);

	for (auto iter = m_Visitor->m_World->m_Actions.begin(); iter != m_Visitor->m_World->m_Actions.end(); ++iter)
	{
		if (!*iter)
		{
			Logger::LogError("Unmapped action index " + std::to_string(int(iter - m_Visitor->m_World->m_Actions.begin())));
		}
		else
		{
			const Action& action = **iter;
			for (size_t i = 0; i < action.m_Names.size(); ++i)
			{
				if (firstWord.compare(action.m_Names[i]) == 0)
				{
					result.m_ActionString = firstWord;
					result.m_ActionType = action.m_Type;
					const size_t actionInputLen = action.m_Names[i].length();
					result.m_RemainingString = input.substr(actionInputLen);
					result.m_ExtraWords = RemoveExtraWordsFromRemainingInput(result.m_RemainingString);
					RemoveLeadingAndTrailingWhiteSpaces(result.m_RemainingString);
					return result;
				}
			}
		}
	}
	return result;
}

std::string TextAdventure::RemoveExtraWordsFromRemainingInput(std::string& remainingString)
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

ApplyInputResult TextAdventure::ApplyInput(World* world, const ParsedInput& parsedInput)
{
	ApplyInputResult result = {};

	switch (parsedInput.m_ActionType)
	{
	case Action_Type::GO:
	{
		Direction direction = StringToDirection(parsedInput.m_RemainingString);
		if (direction != Direction::NONE)
		{
			// This is a valid direction, store it in the output object
			result.m_ExtraInfo = parsedInput.m_RemainingString;
			for (size_t i = 0; i < world->m_CurrentArea->m_Neighbors.size(); i++)
			{
				const auto& neighbor = world->m_CurrentArea->m_Neighbors[i];
				if (neighbor.first)
				{
					if (neighbor.second == direction)
					{
						world->m_CurrentArea = world->m_CurrentArea->m_Neighbors[i].first;
						result.m_Success = true;
						result.m_DescribeAreaAgain = true;
						return result;
					}
				}
			}
		}
		else
		{
			for (size_t i = 0; i < world->m_CurrentArea->m_Neighbors.size(); i++)
			{
				const auto& neighbor = world->m_CurrentArea->m_Neighbors[i];
				if (neighbor.first)
				{
					std::string neighborName = neighbor.first->m_Name;
					std::string noWSInput = parsedInput.m_RemainingString;
					RemoveLeadingAndTrailingWhiteSpaces(noWSInput);
					if (neighborName.compare(noWSInput) == 0)
					{
						world->m_CurrentArea = world->m_CurrentArea->m_Neighbors[i].first;
						result.m_Success = true;
						result.m_ExtraInfo = neighborName;
						result.m_DescribeAreaAgain = true;
						return result;
					}
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
		std::string itemName = parsedInput.m_RemainingString;
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
	{
		if (parsedInput.m_RemainingString.empty())
		{
			IO::OutputString("Did you mean to type quit?");

			result.m_Success = false;

			return result;
		}
	} break;
	case Action_Type::LOOK:
		break;
	case Action_Type::INSPECT:
	{
		std::string itemToBeInspectedName = parsedInput.m_RemainingString;

		for (Item* item : world->m_CurrentArea->m_Items)
		{
			if (item->m_Name.compare(itemToBeInspectedName) == 0)
			{
				std::string itemDescription = item->m_Descriptions[0];

				IO::OutputString(itemDescription);

				result.m_Success = true;
				result.m_DescribeAreaAgain = false;

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
	case Action_Type::NONE:
		break;
	default:
		break;
	}

	result.m_Success = false;
	return result;
}

void TextAdventure::PrintInvalidInputMessage(const ParsedInput& parsedInput, const ApplyInputResult& inputResult)
{
	std::string remainingStringNoWS = parsedInput.m_RemainingString;
	RemoveWhiteSpaces(remainingStringNoWS);

	std::string defaultWarningString = "Sorry, you can't " + parsedInput.m_ActionString + " ";
	if (!parsedInput.m_ExtraWords.empty()) defaultWarningString += parsedInput.m_ExtraWords + " ";
	defaultWarningString += parsedInput.m_RemainingString;

	// TODO: More detailed usage descriptions?
	switch (parsedInput.m_ActionType)
	{
	case Action_Type::GO:
	{
		if (remainingStringNoWS.empty())
		{
			IO::OutputString("Please specify where you want to go");
		}
		else
		{
			IO::OutputString(defaultWarningString);
		}
	} break;
	case Action_Type::TAKE:
	case Action_Type::DROP:
	case Action_Type::EQUIP:
	case Action_Type::EAT:
	case Action_Type::TRADE:
	case Action_Type::GIVE:
	case Action_Type::SPEAK:
	case Action_Type::ENTER:
	case Action_Type::EXIT:
	case Action_Type::INSPECT:
	case Action_Type::READ:
	case Action_Type::ATTACK:
	case Action_Type::THROW:
	{
		IO::OutputString(defaultWarningString);
	} break;
	case Action_Type::LOOK:
		if (remainingStringNoWS.empty())
		{
			IO::OutputString("Please specify what you want to look at");
		}
		else
		{
			IO::OutputString(defaultWarningString);
		}
		break;
	case Action_Type::COMMANDS:
	{
		IO::OutputString("The available commands are: ");
		IO::OutputString("GO, HELP, COMMANDS, INVENTORY, TAKE DROP, EQUIP, EAT, TRADE, GIVE,"
			"SPEAK, ENTER, EXIT, LOOK, INSPECT, READ, ATTACK, THROW, YES, NO");
	} break;
	case Action_Type::HELP:
	{
		IO::OutputString("Type \"commands\" to see all available commands");
	} break;
	case Action_Type::QUIT:
	{
		IO::OutputString("Are you sure you want to quit?");
	} break;

	case Action_Type::INVENTORY:
	case Action_Type::YES:
	case Action_Type::NO:
		// No warning message for these commands
		break;

	case Action_Type::NONE:
	default:
	{
		IO::OutputString("Sorry, that was invalid input!");
		IO::OutputString("Type \"help\" or \"?\" for help");
		IO::OutputString("Type \"commands\" to see all available commands");
	} break;
	}

	IO::OutputNewLine();
}
