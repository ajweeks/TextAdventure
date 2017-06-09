
// 2DAE1
// AJ Weeks

#include "stdafx.h"

#include "TextAdventure.h"
#include "MainVisitor.h"
#include "Logger.h"
#include "IO.h"
#include "World.h"

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

Globals* TextAdventure::gGlobals = nullptr;

TextAdventure::TextAdventure() :
	m_QuitMessage(false),
	m_Playing(true)
{
	if (!TextAdventure::gGlobals)
	{
		TextAdventure::gGlobals = new Globals();
	}
}

TextAdventure::~TextAdventure()
{
	if (TextAdventure::gGlobals)
	{
		delete TextAdventure::gGlobals;
		TextAdventure::gGlobals = nullptr;
	}
}

void TextAdventure::PopulateWordWhitelist() const
{
	// Actions
	for (auto iter = gGlobals->m_Actions.begin(); iter != gGlobals->m_Actions.end(); ++iter)
	{
		const Action* action = (*iter);

		for (auto iter = action->m_Names.begin(); iter != action->m_Names.end(); ++iter)
		{
			gGlobals->m_WorldWhitelist.push_back(*iter);
		}
	}

	// Items
	for (auto iter = gGlobals->m_ItemDefinitions.begin(); iter != gGlobals->m_ItemDefinitions.end(); ++iter)
	{
		gGlobals->m_WorldWhitelist.push_back((*iter)->m_Name);
	}

	// Areas
	for (auto iter = m_Visitor->m_World->m_Areas.begin(); iter != m_Visitor->m_World->m_Areas.end(); ++iter)
	{
		gGlobals->m_WorldWhitelist.push_back((*iter)->m_Name);
	}

	// Directions
	for (size_t i = 0; i < (int)Direction::NONE; ++i)
	{
		gGlobals->m_WorldWhitelist.push_back(DirectionToString(Direction(i)));
		gGlobals->m_WorldWhitelist.push_back(DirectionToShortString(Direction(i)));
	}

	// Player
	gGlobals->m_WorldWhitelist.push_back(m_Visitor->m_World->m_Player->m_Name);
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

		PlayGame();
	}
}

void TextAdventure::PlayGame()
{
	IO::OutputString("Welcome to Pondania!");
	IO::OutputString("");

	bool describeArea = true;
	while (m_Playing)
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

				if (!m_Playing)
				{
					return;
				}
			}

			std::string input;
			std::getline(std::cin, input);
			RemoveLeadingAndTrailingWhiteSpaces(input);
			ToLower(input);
			parsedInput = ParseInput(input);

			ApplyInput(parsedInput);
		} while (!parsedInput.m_Success);

		describeArea = parsedInput.m_DescribeAreaAgain;

		if (!parsedInput.m_SuccessText.empty())
		{
			IO::OutputString(parsedInput.m_SuccessText);
		}

		if (m_Visitor->m_World->m_CurrentArea->m_Name.compare("escape hatch") == 0)
		{
			// The player escaped! Game oversq	qqqqqqq
			m_Playing = false;

			m_Visitor->m_World->m_CurrentArea->Describe();

			IO::OutputString("Thank you for playing! Press any key to exit ...");
			IO::InputLine();
		}
	}
}

ParsedInput TextAdventure::ParseInput(const std::string& input) const
{
	ParsedInput result = {};

	std::string inputCopy = input;

	// Add spaces to front and back for easier parsing
	inputCopy = ' ' + inputCopy + ' ';

	bool marked;
	do
	{
		marked = false;

		for (std::string whiteListWord : gGlobals->m_WorldWhitelist)
		{
			// Surround with spaces to ensure we're not finding the 'e' in 'exit' for example
			// and mistaking it for the e commandBedroom
			const size_t findResult = inputCopy.find(' ' + whiteListWord + ' ');
			if (findResult != std::string::npos)
			{
				const auto wordStartIt = inputCopy.begin() + findResult + 1;
				const auto wordEndIt = wordStartIt + whiteListWord.length();
				const std::string removedWord = std::string(wordStartIt, wordEndIt);
				inputCopy.erase(findResult + 1, whiteListWord.length());
				marked = true;

				// Find out if word is an action
				const auto actionIt = std::find_if(gGlobals->m_Actions.begin(), gGlobals->m_Actions.end(),
					[&removedWord](const Action* action) 
					{ 
						return Contains(action->m_Names, removedWord); 
					});
				
				Area* const currentArea = m_Visitor->m_World->m_CurrentArea;
				const auto areaIt = std::find_if(currentArea->m_Neighbors.begin(), currentArea->m_Neighbors.end(),
					[&removedWord](const std::pair<Area*, Direction>& pair) 
					{ 
						return pair.first ? pair.first->m_Name.compare(removedWord) == 0 : false; 
					});
				
				const auto areaItemIt = std::find_if(currentArea->m_Items.begin(), currentArea->m_Items.end(), 
					[&removedWord](const Item* const item)
					{
						return item->m_Name.compare(removedWord) == 0;
					});

				const auto inventoryItemIt = std::find_if(m_Visitor->m_World->m_Player->m_Inventory.begin(), m_Visitor->m_World->m_Player->m_Inventory.end(),
					[&removedWord](const Item* const item)
					{
						return item->m_Name.compare(removedWord) == 0;
					});

				const Direction direction = StringToDirection(removedWord);

				if (actionIt != gGlobals->m_Actions.end())
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
				else if (areaItemIt != m_Visitor->m_World->m_CurrentArea->m_Items.end())
				{
					if (result.m_Item == nullptr)
					{
						result.m_Item = (*areaItemIt);
					}
				}
				else if (inventoryItemIt != m_Visitor->m_World->m_Player->m_Inventory.end())
				{
					if (result.m_Item == nullptr)
					{
						result.m_Item = (*inventoryItemIt);
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
					result.m_NounString = removedWord;
				}

				break;
			}
		}
	} while (marked);

	result.m_Extra = inputCopy;
	RemoveLeadingAndTrailingWhiteSpaces(result.m_Extra);
	if (result.m_Extra.empty())
	{
		result.m_Extra = result.m_NounString;
	}

	return result;
}

void TextAdventure::ApplyInput(ParsedInput& parsedInput) const
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
			const auto pair = m_Visitor->m_World->m_CurrentArea->m_Neighbors[(int)parsedInput.m_Direction];
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
			bool validAreaName = false;
			for (size_t i = 0; i < m_Visitor->m_World->m_Areas.size(); i++)
			{
				if (m_Visitor->m_World->m_Areas[i]->m_Name.compare(parsedInput.m_NounString) == 0)
				{
					validAreaName = true;
					break;
				}
			}

			if (validAreaName)
			{
				parsedInput.m_ErrorMessage = "You can't reach that room from here!";
			}
			else
			{
				parsedInput.m_ErrorMessage = "That's not a valid area name!";
			}
		}
	} break;
	case Action_Type::INVENTORY:
		IO::OutputString(m_Visitor->m_World->m_Player->DescribeInventory());
		break;
	case Action_Type::TAKE:
	{
		if (parsedInput.m_Item)
		{
			bool itemExistsInCurrentArea = false;
			for (size_t i = 0; i < m_Visitor->m_World->m_CurrentArea->m_Items.size(); i++)
			{
				if (m_Visitor->m_World->m_CurrentArea->m_Items[i]->m_Name.compare(parsedInput.m_Item->m_Name) == 0)
				{
					itemExistsInCurrentArea = true;
					break;
				}
			}

			if (itemExistsInCurrentArea)
			{
				m_Visitor->m_World->m_CurrentArea->RemoveItem(parsedInput.m_Item);

				m_Visitor->m_World->m_Player->m_Inventory.push_back(parsedInput.m_Item);
				parsedInput.m_SuccessText = "You picked up a " + parsedInput.m_Item->m_Name;
				parsedInput.m_Success = true;
				return;
			}
			else
			{
				parsedInput.m_ErrorMessage = "That item doesn't exist here!";
			}
		}
	} break;
	case Action_Type::DROP:
		if (parsedInput.m_Item)
		{
			Player* player = m_Visitor->m_World->m_Player;
			
			auto iter = player->IsItemInInventory(parsedInput.m_Item);
			if (iter != player->m_Inventory.end())
			{
				parsedInput.m_Success = true;
				parsedInput.m_DescribeAreaAgain = true;

				player->RemoveItemFromInventory(iter);
				m_Visitor->m_World->m_CurrentArea->AddItem(parsedInput.m_Item);

				return;
			}
		}
		break;
	case Action_Type::INSPECT:
	{
		if (parsedInput.m_Item != nullptr)
		{
			int descIndex = rand() % parsedInput.m_Item->m_Descriptions.size();
			const std::string itemDescription = parsedInput.m_Item->m_Descriptions[descIndex];
			IO::OutputString(itemDescription);

			parsedInput.m_Success = true;
			parsedInput.m_DescribeAreaAgain = false;

			return;
		}
		else if (parsedInput.m_Area != nullptr)
		{
			const std::string itemDescription = parsedInput.m_Area->m_Description;
			IO::OutputString(itemDescription);

			parsedInput.m_Success = true;
			parsedInput.m_DescribeAreaAgain = false;

			return;
		}
		else if (parsedInput.m_Player != nullptr)
		{
			const std::string itemDescription = parsedInput.m_Player->DescribeInventory();
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
	case Action_Type::OPEN:
	{
		if (parsedInput.m_Item)
		{
			if (parsedInput.m_Item->m_Name.compare("locked doors") == 0)
			{
				if (!parsedInput.m_Item->m_RequiredItems.empty())
				{
					bool success = true;
					const std::vector<Item*>& inventory = m_Visitor->m_World->m_Player->m_Inventory;
					
					if (inventory.size() < parsedInput.m_Item->m_RequiredItems.size())
					{
						success = false;
					}
					else
					{
						for (size_t i = 0; i < inventory.size(); i++)
						{
							if (!Contains(inventory, parsedInput.m_Item->m_RequiredItems[i]))
							{
								success = false;
								break;
							}
						}
					}

					if (success)
					{
						// Unlock the doors
						parsedInput.m_Item->m_Activated = true;
						m_Visitor->m_World->m_CurrentArea = m_Visitor->m_World->m_CurrentArea->m_OnSuccessArea;
						parsedInput.m_DescribeAreaAgain = true;
						parsedInput.m_Success = true;
						return;
					}
					else
					{
						parsedInput.m_ErrorMessage = "You can't open " + parsedInput.m_Item->m_Name;
					}
				}
			}
		}
	} break;
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

	std::string noun = parsedInput.m_Extra;
	if (noun.empty()) noun = parsedInput.m_NounString;
	if (noun.empty()) noun = "that";
	const std::string defaultWarningString = "Sorry, you can't " + parsedInput.m_InputActionString + " " + parsedInput.m_Extra;

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
	case Action_Type::INSPECT:
	{
		IO::OutputString(defaultWarningString);
	} break;
	case Action_Type::OPEN:
	{
		IO::OutputString(parsedInput.m_ErrorMessage);
	} break;
	case Action_Type::COMMANDS:
	{
		IO::OutputString("The available commands are: ");
		IO::OutputString("GO, HELP, INVENTORY, TAKE, DROP, ENTER, EXIT, INSPECT, QUIT");
	} break;
	case Action_Type::HELP:
	{
		IO::OutputString("Type \"commands\" to see all available commands");
	} break;
	case Action_Type::QUIT:
	{
		if (m_QuitMessage)
		{
			m_Playing = false;
		}
		else
		{
			m_QuitMessage = true;
			IO::OutputString("Are you sure you want to quit?");
		}
	} break;

	case Action_Type::INVENTORY:
		break;
	case Action_Type::YES:
		if (m_QuitMessage)
		{
			m_Playing = false;
		}
		break;
	case Action_Type::NO:
		if (m_QuitMessage)
		{
			m_QuitMessage = false;
		}
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
