
// 2DAE1
// AJ Weeks

#include "stdafx.h"

#include "TextAdventure.h"
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

Globals TextAdventure::gGlobals = {};

TextAdventure::TextAdventure()
{
}

void TextAdventure::PopulateWordWhitelist()
{
	// Actions
	for (auto iter = gGlobals.m_Actions.begin(); iter != gGlobals.m_Actions.end(); ++iter)
	{
		Action* action = (*iter);

		for (auto iter = action->m_Names.begin(); iter != action->m_Names.end(); ++iter)
		{
			gGlobals.m_WorldWhitelist.push_back(*iter);
		}
	}

	// Items
	for (auto iter = gGlobals.m_ItemDefinitions.begin(); iter != gGlobals.m_ItemDefinitions.end(); ++iter)
	{
		gGlobals.m_WorldWhitelist.push_back((*iter)->m_Name);
	}

	// Areas
	for (auto iter = m_Visitor->m_World->m_Areas.begin(); iter != m_Visitor->m_World->m_Areas.end(); ++iter)
	{
		gGlobals.m_WorldWhitelist.push_back((*iter)->m_Name);
	}

	// Directions
	for (size_t i = 0; i < (int)Direction::NONE; ++i)
	{
		gGlobals.m_WorldWhitelist.push_back(DirectionToString(Direction(i)));
		gGlobals.m_WorldWhitelist.push_back(DirectionToShortString(Direction(i)));
	}

	// Player
	gGlobals.m_WorldWhitelist.push_back(m_Visitor->m_World->m_Player->m_Name);
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

		PopulateWordWhitelist();

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
		parsedInput.m_Success = true; // Don't print the warning the first time through the loop
		parsedInput.m_DescribeAreaAgain = true;
		do
		{
			if (!parsedInput.m_Success)
			{
				PrintInvalidInputMessage(parsedInput);
			}

			std::string input;
			std::getline(std::cin, input);
			RemoveLeadingAndTrailingWhiteSpaces(input);
			ToLower(input);
			parsedInput = ParseInput(input);

			ApplyInput(parsedInput);
		} while (!parsedInput.m_Success);


		describeArea = parsedInput.m_DescribeAreaAgain;

		//ClearConsole();
	}
}

ParsedInput TextAdventure::ParseInput(const std::string& input)
{
	ParsedInput result = {};

	std::string inputCopy = input;
	// Add spaces to front and back for easier parsing
	inputCopy = ' ' + inputCopy + ' ';

	bool marked;
	do
	{
		marked = false;

		for (std::string whiteListWord : gGlobals.m_WorldWhitelist)
		{
			// Surround with spaces to ensure we're not finding the 'e' in 'exit' for example
			// and mistaking it for the e commandBedroom
			const size_t findResult = inputCopy.find(' ' + whiteListWord + ' ');
			if (findResult != std::string::npos)
			{
				auto wordStartIt = inputCopy.begin() + findResult + 1;
				auto wordEndIt = wordStartIt + whiteListWord.length();
				const std::string removedWord = std::string(wordStartIt, wordEndIt);
				inputCopy.erase(findResult + 1, whiteListWord.length());
				marked = true;

				// Find out if word is an action
				auto actionIt = std::find_if(gGlobals.m_Actions.begin(), gGlobals.m_Actions.end(),
					[&removedWord](Action* action) { return Contains(action->m_Names, removedWord); });
				//auto actionIt = gStringToActionType.find(removedWord);
				
				auto areaIt = std::find_if(m_Visitor->m_World->m_CurrentArea->m_Neighbors.begin(), m_Visitor->m_World->m_CurrentArea->m_Neighbors.end(),
					[&removedWord](std::pair<Area*, Direction> pair) { return pair.first ? pair.first->m_Name.compare(removedWord) == 0 : false; });
				
				auto itemIt = std::find_if(m_Visitor->m_World->m_CurrentArea->m_Items.begin(), m_Visitor->m_World->m_CurrentArea->m_Items.end(),
					[&removedWord](Item* item) { return item->m_Name.compare(removedWord) == 0; });
				
				Direction direction = StringToDirection(removedWord);

				if (actionIt != gGlobals.m_Actions.end())
				{
					if (result.m_Action == nullptr)
					{
						result.m_InputActionString = removedWord;
						result.m_Action = (*actionIt);
					}
				}
				else if (areaIt != m_Visitor->m_World->m_CurrentArea->m_Neighbors.end())
				{
					if (result.m_Area == nullptr)
					{
						result.m_Area = areaIt->first;
					}
				}
				else if (itemIt != m_Visitor->m_World->m_CurrentArea->m_Items.end())
				{
					if (result.m_Item == nullptr)
					{
						result.m_Item = (*itemIt);
					}
				}
				else if (m_Visitor->m_World->m_CurrentArea->m_Name.compare(removedWord) == 0)
				{
					if (result.m_Area == nullptr)
					{
						result.m_Area = m_Visitor->m_World->m_CurrentArea;
					}
				}
				else if (direction != Direction::NONE)
				{
					if (result.m_Direction == Direction::NONE)
					{
						result.m_Direction = direction;
					}
				}
				else if (m_Visitor->m_World->m_Player->m_Name.compare(removedWord) == 0)
				{
					if (result.m_Player == nullptr)
					{
						result.m_Player = m_Visitor->m_World->m_Player;
					}
				}
				else
				{
					Logger::LogInfo("Unhandled white list word parsed in: " + removedWord);
					result.m_Extra.append(removedWord);
				}

				break;
			}
		}
	} while (marked);

	result.m_Extra = inputCopy;
	RemoveLeadingAndTrailingWhiteSpaces(result.m_Extra);

	return result;
}

void TextAdventure::ApplyInput(ParsedInput& parsedInput)
{
	if (!parsedInput.m_Action)
	{
		parsedInput.m_ErrorMessage = "I didn't understand that";

		parsedInput.m_Success = false;
		parsedInput.m_DescribeAreaAgain = true;
		return;
	}

	switch (parsedInput.m_Action->m_Type)
	{
	case Action_Type::GO:
	{
		if (parsedInput.m_Direction != Direction::NONE)
		{
			// This is a valid direction, store it in the output object
			auto pair = m_Visitor->m_World->m_CurrentArea->m_Neighbors[(int)parsedInput.m_Direction];
			assert(pair.second == parsedInput.m_Direction);

			if (pair.first != nullptr)
			{
				m_Visitor->m_World->m_CurrentArea = pair.first;
				parsedInput.m_Success = true;
				parsedInput.m_DescribeAreaAgain = true;
				return;
			}
			else
			{
				parsedInput.m_ErrorMessage = "Sorry, you can't go that direction!";
			}
		}
		else if (parsedInput.m_Area != nullptr)
		{
			m_Visitor->m_World->m_CurrentArea = parsedInput.m_Area;
			parsedInput.m_Success = true;
			parsedInput.m_Extra = parsedInput.m_Area->m_Name;
			parsedInput.m_DescribeAreaAgain = true;
			return;
		}
		else
		{
			parsedInput.m_ErrorMessage = "That's not a valid area name!";
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
		if (parsedInput.m_Item == nullptr)
		{
			parsedInput.m_ErrorMessage = "You can't eat that!";
		}
		else
		{
			IO::OutputString("Yum");
			m_Visitor->m_World->m_CurrentArea->RemoveItem(parsedInput.m_Item);
			parsedInput.m_Success = true;
			return;
		}
	} break;
	case Action_Type::TRADE:
		break;
	case Action_Type::GIVE:
		break;
	case Action_Type::SPEAK:
		break;
	case Action_Type::LOOK:
		break;
	case Action_Type::INSPECT:
	{
		if (parsedInput.m_Item != nullptr)
		{
			std::string itemDescription = parsedInput.m_Item->m_Descriptions[0];

			IO::OutputString(itemDescription);

			parsedInput.m_Success = true;
			parsedInput.m_DescribeAreaAgain = false;

			return;
		}
		else if (parsedInput.m_Area != nullptr)
		{
			std::string itemDescription = parsedInput.m_Area->m_Description;

			IO::OutputString(itemDescription);

			parsedInput.m_Success = true;
			parsedInput.m_DescribeAreaAgain = false;

			return;
		}
		else if (parsedInput.m_Player != nullptr)
		{
			std::string itemDescription = parsedInput.m_Player->DescribeInventory();

			IO::OutputString(itemDescription);

			parsedInput.m_Success = true;
			parsedInput.m_DescribeAreaAgain = false;

			return;
		}
		else
		{
			parsedInput.m_ErrorMessage = "That item isn't in this area";
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

	parsedInput.m_Success = false;
}

void TextAdventure::PrintInvalidInputMessage(const ParsedInput& parsedInput)
{
	std::string remainingStringNoWS = parsedInput.m_Extra;
	RemoveWhiteSpaces(remainingStringNoWS);

	std::string defaultWarningString = "Sorry, you can't " + parsedInput.m_InputActionString + " " + parsedInput.m_Extra;

	if (!parsedInput.m_Action)
	{
		IO::OutputString(parsedInput.m_ErrorMessage);
		return;
	}

	// TODO: More detailed usage descriptions?
	switch (parsedInput.m_Action->m_Type)
	{
	case Action_Type::GO:
	{
		IO::OutputString(parsedInput.m_ErrorMessage);
	} break;
	case Action_Type::TAKE:
	case Action_Type::DROP:
	case Action_Type::EQUIP:
	case Action_Type::EAT:
	case Action_Type::TRADE:
	case Action_Type::GIVE:
	case Action_Type::SPEAK:
	case Action_Type::INSPECT:
	case Action_Type::READ:
	case Action_Type::ATTACK:
	case Action_Type::THROW:
	{
		IO::OutputString(defaultWarningString);
	} break;
	case Action_Type::LOOK:
	{
		if (remainingStringNoWS.empty())
		{
			IO::OutputString("Please specify what you want to look at");
		}
		else
		{
			IO::OutputString(defaultWarningString);
		}
	} break;
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
