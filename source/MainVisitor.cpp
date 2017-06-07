
#include "stdafx.h"

#include "MainVisitor.h"
#include "Logger.h"
#include "TextAdventure.h"

using namespace antlrcpp;

MainVisitor::MainVisitor()
{
}

MainVisitor::~MainVisitor()
{
}

antlrcpp::Any MainVisitor::visitWorld(textworldParser::WorldContext* context)
{
	assert(m_World == nullptr);

	m_World = new World();

	return visitChildren(context);
}

antlrcpp::Any MainVisitor::visitPlayer(textworldParser::PlayerContext* context)
{
	assert(m_World->m_Player == nullptr);

	m_World->m_Player = new Player();

	m_LastVisitedType = textworldParser::PLAYER;
	m_LastVisitedIndex = 0;

	return visitChildren(context);
}

antlrcpp::Any MainVisitor::visitItem(textworldParser::ItemContext* context)
{
	Item* newItem = new Item();
	TextAdventure::gGlobals->m_ItemDefinitions.push_back(newItem);

	m_LastVisitedType = textworldParser::ITEM;
	m_LastVisitedIndex = TextAdventure::gGlobals->m_ItemDefinitions.size() - 1;

	return visitChildren(context);
}

antlrcpp::Any MainVisitor::visitArea(textworldParser::AreaContext* context)
{
	Area* newArea = new Area();
	m_World->m_Areas.push_back(newArea);

	m_LastVisitedType = textworldParser::AREA;
	m_LastVisitedIndex = m_World->m_Areas.size() - 1;

	if (!m_World->m_CurrentArea)
	{
		m_World->m_CurrentArea = m_World->m_Areas[0];
	}

	return visitChildren(context);
}

antlrcpp::Any MainVisitor::visitAction(textworldParser::ActionContext* context)
{
	const std::string name = context->ID()->getSymbol()->getText();
	
	Action* newAction = new Action();

	if (gStringToActionType.find(name) == gStringToActionType.end())
	{
		Logger::LogWarning("Action type not found in global string to action map " + name);
	}

	Action_Type type = gStringToActionType[name];
	newAction->m_Type = type;
	const int typeIndex = (int)type;
	
	assert(typeIndex < TextAdventure::gGlobals->m_Actions.size());

	TextAdventure::gGlobals->m_Actions[typeIndex] = newAction;

	m_LastVisitedType = textworldParser::ACTION;
	m_LastVisitedIndex = typeIndex;

	return visitChildren(context);
}

antlrcpp::Any MainVisitor::visitAssignment(textworldParser::AssignmentContext* context)
{
	textworldParser::ValueContext* valueContext = context->value();
	const std::string assignmentTypeStr = context->ID()->getSymbol()->getText();
	if (valueContext->STRING() != nullptr)
	{
		std::string str = valueContext->STRING()->getSymbol()->getText();
		RemoveCharFromString(str, '"');

		if (str.find("\n") != std::string::npos)
		{
			const std::vector<std::string> strings = Split(str);
			for (size_t i = 0; i < strings.size(); i++)
			{
				const std::string assignmentValue = strings[i];
				AssignParsedValue(assignmentTypeStr, assignmentValue);
			}
		}
		else
		{
			AssignParsedValue(assignmentTypeStr, str);
		}
	}
	else if (valueContext->INT() != nullptr)
	{
		const std::string assignmentValue = valueContext->INT()->getSymbol()->getText();
		AssignParsedValue(assignmentTypeStr, assignmentValue);
	}

	return visitChildren(context);
}

antlrcpp::Any MainVisitor::visitValue(textworldParser::ValueContext* context)
{
	const auto values = context->value();

	for (size_t i = 0; i < values.size(); i++)
	{
		textworldParser::AssignmentContext* castedParent = static_cast<textworldParser::AssignmentContext*>(context->parent);
		const std::string assignmentTypeStr = castedParent->ID()->getSymbol()->getText();

		std::string assignmentValue = values[i]->getText();
		RemoveCharFromString(assignmentValue, '"');

		AssignParsedValue(assignmentTypeStr, assignmentValue);
	}

	return visitChildren(context);
}

void MainVisitor::AssignParsedValue(const std::string& assignmentTypeStr, const std::string& assignmentValue)
{
	switch (m_LastVisitedType)
	{
	case textworldParser::ITEM:
	{
		Item* item = TextAdventure::gGlobals->m_ItemDefinitions[m_LastVisitedIndex];

		if (assignmentTypeStr.compare("name") == 0)
		{
			item->m_Name = assignmentValue;
			ToLower(item->m_Name);
		}
		else if (assignmentTypeStr.compare("descriptions") == 0)
		{
			item->m_Descriptions.push_back(assignmentValue);
		}
		else if (assignmentTypeStr.compare("requiredItems") == 0)
		{
			item->m_RequiredItems.push_back(GetItemByName(assignmentValue));
		}
		else if (assignmentTypeStr.compare("actions") == 0)
		{
			std::string actionClean = assignmentValue;
			ToLower(actionClean);

			Action* action = TextAdventure::gGlobals->m_Actions[(int)gStringToActionType[actionClean]];
			assert(action != nullptr);
			item->m_Actions.push_back(action);
		}
		else if (assignmentTypeStr.compare("onSuccessDescriptions") == 0)
		{
			item->m_OnSuccessDescriptions.push_back(assignmentValue);
		}
		else
		{
			Logger::LogWarning("Unhandled assignment type to item: " + assignmentTypeStr + " of " + assignmentValue);
		}
	} break;
	case textworldParser::ACTION:
	{
		Action* action = TextAdventure::gGlobals->m_Actions[m_LastVisitedIndex];

		if (assignmentTypeStr.compare("names") == 0)
		{
			std::string actionNameClean = assignmentValue;
			ToLower(actionNameClean);
			action->m_Names.push_back(actionNameClean);
		}
		else
		{
			Logger::LogWarning("Unhandled assignment type to action: " + assignmentTypeStr + " of " + assignmentValue);
		}
	} break;
	case textworldParser::AREA:
	{
		Area* area = m_World->m_Areas[m_LastVisitedIndex];

		if (assignmentTypeStr.compare("name") == 0)
		{
			area->m_Name = assignmentValue;
			ToLower(area->m_Name);
		}
		else if (assignmentTypeStr.compare("neighbors") == 0)
		{
			AddNeighborString(area->m_Name, assignmentValue);
		}
		else if (assignmentTypeStr.compare("description") == 0)
		{
			area->m_Description = assignmentValue;
		}
		else if (assignmentTypeStr.compare("items") == 0)
		{
			Item* item = GetItemByName(assignmentValue);

			if (item)
			{
				area->m_Items.push_back(item);
			}
			else
			{
				Logger::LogError("Couldn't find item with name " + assignmentValue);
			}
		}
		else if (assignmentTypeStr.compare("onSuccessArea") == 0)
		{
			m_NeighborStrings[m_LastVisitedIndex].onSuccessAreaName = assignmentValue;
		}
		else
		{
			Logger::LogWarning("Unhandled assignment type to area: " + assignmentTypeStr + " of " + assignmentValue);
		}
		} break;
	case textworldParser::PLAYER:
	{
		if (assignmentTypeStr.compare("name") == 0)
		{
			m_World->m_Player->m_Name = assignmentValue;
		}
		else if (assignmentTypeStr.compare("inventory") == 0)
		{
			Item* item = GetItemByName(assignmentValue);

			if (item)
			{
				m_World->m_Player->m_Inventory.push_back(item);
			}
			else
			{
				Logger::LogError("Couldn't find item with name " + assignmentValue);
			}
		}
		else
		{
			Logger::LogWarning("Unhandled assignment type to player: " + assignmentTypeStr + " of " + assignmentValue);
		}
	} break;
	}
}

void MainVisitor::AddNeighborString(const std::string& areaName, const std::string& neighborName)
{
	std::string areaNameClean = areaName;
	ToLower(areaNameClean);

	bool foundArea = false;
	for (size_t i = 0; i < m_NeighborStrings.size(); i++)
	{
		if (m_NeighborStrings[i].areaName.compare(areaNameClean) == 0)
		{
			AddNeighborString(i, neighborName);
			foundArea = true;
			break;
		}
	}

	// This area hasn't been added to the list of neighbors yet
	if (!foundArea)
	{
		m_NeighborStrings.push_back({});
		const size_t areaIndex = m_NeighborStrings.size() - 1;
		m_NeighborStrings[areaIndex].areaName = areaNameClean;
		ToLower(m_NeighborStrings[areaIndex].areaName);
		AddNeighborString(areaIndex, neighborName);
	}
}

void MainVisitor::AddNeighborString(size_t areaIndex, const std::string& neighborName)
{
	std::string neighborNameClean = neighborName;
	ToLower(neighborNameClean);

	AreaNeighbor& areaArr = m_NeighborStrings[areaIndex];

	for (size_t i = 0; i < areaArr.neighborNames.size(); ++i)
	{
		if (areaArr.neighborNames[i].empty())
		{
			areaArr.neighborNames[i] = neighborNameClean;
			return;
		}
	}

	Logger::LogError("Area " + areaArr.areaName + " has too many neighbors (should have 4)", true);
}

Item* MainVisitor::GetItemByName(const std::string& itemName) const
{
	Item* result = nullptr;

	std::string itemNameClean = itemName;
	ToLower(itemNameClean);

	for (size_t i = 0; i < TextAdventure::gGlobals->m_ItemDefinitions.size(); i++)
	{
		if (TextAdventure::gGlobals->m_ItemDefinitions[i]->m_Name.compare(itemNameClean) == 0)
		{
			result = TextAdventure::gGlobals->m_ItemDefinitions[i];
			break;
		}
	}

	return result;
}

Area* MainVisitor::GetAreaByName(const std::string & areaName) const
{
	Area* result = nullptr;

	std::string areaNameClean = areaName;
	ToLower(areaNameClean);

	for (size_t i = 0; i < m_World->m_Areas.size(); i++)
	{
		if (m_World->m_Areas[i]->m_Name.compare(areaNameClean) == 0)
		{
			result = m_World->m_Areas[i];
			break;
		}
	}

	return result;
}

void MainVisitor::PostVisit() const
{
	assert(m_World->m_Areas.size() == m_NeighborStrings.size());

	for (size_t i = 0; i < m_NeighborStrings.size(); i++)
	{
		const AreaNeighbor& areaNeighbor = m_NeighborStrings[i];

		if (!areaNeighbor.onSuccessAreaName.empty())
		{
			m_World->m_Areas[i]->m_OnSuccessArea = GetAreaByName(areaNeighbor.onSuccessAreaName);
		}

		for (size_t j = 0; j < areaNeighbor.neighborNames.size(); j++)
		{
			const std::string& neighborString = areaNeighbor.neighborNames[j];
			const Direction direction = (Direction)j;

			if (neighborString.compare("0") == 0)
			{
				AddNeighborPair(m_World->m_Areas[i], { nullptr, direction });
				continue;
			}

			Area* area = nullptr;

			for (auto iter = m_World->m_Areas.begin(); iter != m_World->m_Areas.end(); ++iter)
			{
				if ((*iter)->m_Name.compare(neighborString) == 0)
				{
					area = *iter;
					break;
				}
			}

			if (area)
			{
				AddNeighborPair(m_World->m_Areas[i], { area, direction });
			}
			else
			{
				Logger::LogWarning("Couldn't find neighbor " + neighborString + " in area " + areaNeighbor.areaName +
					" (direction: " + DirectionToString(direction) + ")");
			}
		}
	}
}

void MainVisitor::AddNeighborPair(Area* area, std::pair<Area*, Direction> pair) const
{
	assert(pair.second != Direction::NONE);
	assert(area->m_Neighbors[(size_t)pair.second].first == nullptr);
	if (pair.first) assert(pair.first->m_Name.compare(area->m_Name) != 0);

	area->m_Neighbors[(size_t)pair.second] = pair;
}
