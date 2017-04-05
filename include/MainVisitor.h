#pragma once

#include "structs.h"

#include "textworldBaseVisitor.h"

#include <vector>

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

	void PostVisit();

	World* m_World = nullptr;

private:
	void AssignParsedValue(const std::string& assignmentTypeStr, const std::string& assignmentValue);

	int m_LastVisitedType; // Stores the last visited type (area, item, action, etc.)
	int m_LastVisitedIndex;

	// Keeps track of the strings of neighbors we read in, so 
	// we can get the correct pointers to each area's neighbors
	// after all areas have been parsed in
	std::vector<std::vector<std::string>> m_NeighborStrings;

};