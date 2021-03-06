#pragma once

#include "textworldBaseVisitor.h"

#include <vector>
#include <array>

class MainVisitor : public textworldBaseVisitor
{
public:
	MainVisitor();
	virtual ~MainVisitor();

	virtual antlrcpp::Any visitWorld(textworldParser::WorldContext* context) override;
	virtual antlrcpp::Any visitPlayer(textworldParser::PlayerContext* context) override;
	virtual antlrcpp::Any visitItem(textworldParser::ItemContext* context) override;
	virtual antlrcpp::Any visitArea(textworldParser::AreaContext* context) override;
	virtual antlrcpp::Any visitAction(textworldParser::ActionContext* context) override;
	virtual antlrcpp::Any visitValue(textworldParser::ValueContext* context) override;
	virtual antlrcpp::Any visitAssignment(textworldParser::AssignmentContext* context) override;

	void PostVisit() const;

	World* m_World = nullptr;

private:
	void AssignParsedValue(const std::string& assignmentTypeStr, const std::string& assignmentValue);

	void AddNeighborString(const std::string& areaName, const std::string& neighborName);
	void AddNeighborString(size_t areaIndex, const std::string& neighborName);
	void AddNeighborPair(Area* area, std::pair<Area*, Direction> pair) const;

	Item* GetItemByName(const std::string& itemName) const;
	Area* GetAreaByName(const std::string& areaName) const;

	size_t m_LastVisitedType; // Stores the last visited type (area, item, action, etc.)
	size_t m_LastVisitedIndex;

	struct AreaNeighbor
	{
		std::string areaName;
		std::array<std::string, 4> neighborNames;
		std::string onSuccessAreaName;
	};

	// Keeps track of the neighbors we read in, so 
	// we can get the correct pointers to each area's neighbors
	// after all areas have been parsed in
	std::vector<AreaNeighbor> m_NeighborStrings;
};