
#include "MainVisitor.h"
#include "helpers.h"
#include "Logger.h"

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
	m_World->m_Items.push_back(newItem);

	m_LastVisitedType = textworldParser::ITEM;
	m_LastVisitedIndex = m_World->m_Items.size() - 1;

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
	
	assert(typeIndex < m_World->m_Actions.size());

	m_World->m_Actions[typeIndex] = newAction;

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
			std::vector<std::string> strings = Split(str);
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
	auto values = context->value();

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
		Item* item = m_World->m_Items[m_LastVisitedIndex];

		if (assignmentTypeStr.compare("name") == 0)
		{
			item->m_Name = assignmentValue;
		}
		else if (assignmentTypeStr.compare("descriptions") == 0)
		{
			item->m_Descriptions.push_back(assignmentValue);
		}
		else if (assignmentTypeStr.compare("actions") == 0)
		{
			Action* action = m_World->m_Actions[(int)gStringToActionType[assignmentValue]];
			item->m_Actions.push_back(action);
		}
		else
		{
			Logger::LogWarning("Unhandled assignment type to item in MainVistor: " + assignmentTypeStr + " of " + assignmentValue);
		}
	} break;
	case textworldParser::ACTION:
	{
		Action* action = m_World->m_Actions[m_LastVisitedIndex];

		if (assignmentTypeStr.compare("names") == 0)
		{
			action->m_Names.push_back(assignmentValue);
		}
		else
		{
			Logger::LogWarning("Unhandled assignment type to action in MainVistor: " + assignmentTypeStr + " of " + assignmentValue);
		}
	} break;
	case textworldParser::AREA:
	{
		Area* area = m_World->m_Areas[m_LastVisitedIndex];

		if (assignmentTypeStr.compare("name") == 0)
		{
			area->m_Name = assignmentValue;
		}
		else if (assignmentTypeStr.compare("neighbors") == 0)
		{
			// NOTE: Don't store neighbors directly here - there are likely areas
			// that we are neighbors to that haven't been constructed yet, just store
			// the vector of strings for now
			bool foundArea = false;
			for (size_t i = 0; i < m_NeighborStrings.size(); i++)
			{
				if (m_NeighborStrings[i].areaName.compare(area->m_Name) == 0)
				{
					AddNeighborString(i, assignmentValue);
					foundArea = true;
					break;
				}
			}

			// This area hasn't been added to the list of neighbors yet
			if (!foundArea)
			{
				m_NeighborStrings.push_back({});
				const size_t areaIndex = m_NeighborStrings.size() - 1;
				m_NeighborStrings[areaIndex].areaName = area->m_Name;
				AddNeighborString(areaIndex, assignmentValue);
			}
		}
		else if (assignmentTypeStr.compare("description") == 0)
		{
			area->m_Description = assignmentValue;
		}
		else if (assignmentTypeStr.compare("items") == 0)
		{
			Item* item = nullptr;

			for (size_t i = 0; i < m_World->m_Items.size(); i++)
			{
				if (m_World->m_Items[i]->m_Name.compare(assignmentValue) == 0)
				{
					item = m_World->m_Items[i];
					break;
				}
			}


			if (item)
			{
				area->m_Items.push_back(item);
			}
			else
			{
				Logger::LogError("Couldn't find item " + assignmentValue + " in area " + area->m_Name + "!");
			}
		}
		else
		{
			Logger::LogWarning("Unhandled assignment type to area in MainVistor: " + assignmentTypeStr + " of " + assignmentValue);
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
			Item* item;
			m_World->m_Player->m_Inventory.push_back(item);
		}
		else
		{
			Logger::LogWarning("Unhandled assignment type to player in MainVistor: " + assignmentTypeStr + " of " + assignmentValue);
		}
	} break;
	}
}

void MainVisitor::AddNeighborString(size_t areaIndex, const std::string& neighborName)
{
	AreaNeighbor& areaArr = m_NeighborStrings[areaIndex];

	for (size_t i = 0; i < areaArr.neighborNames.size(); ++i)
	{
		if (areaArr.neighborNames[i].empty())
		{
			areaArr.neighborNames[i] = neighborName;
			return;
		}
	}

	Logger::LogError("Area " + areaArr.areaName + " has too many neighbors (should have 4)", true);
}

void MainVisitor::PostVisit()
{
	assert(m_World->m_Areas.size() == m_NeighborStrings.size());

	for (size_t i = 0; i < m_NeighborStrings.size(); i++)
	{
		const AreaNeighbor& areaNeighbor = m_NeighborStrings[i];

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

void MainVisitor::AddNeighborPair(Area* area, std::pair<Area*, Direction> pair)
{
	assert(pair.second != Direction::NONE);
	assert(area->m_Neighbors[(size_t)pair.second].first == nullptr);
	area->m_Neighbors[(size_t)pair.second] = pair;
}
