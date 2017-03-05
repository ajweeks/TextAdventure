#pragma once

#include "textworldBaseVisitor.h"

class MainVisitor : public textworldBaseVisitor
{
public:
	MainVisitor();
	virtual ~MainVisitor();

	virtual antlrcpp::Any visitItem(textworldParser::ItemContext *context) override;

	virtual antlrcpp::Any visitAssignment(textworldParser::AssignmentContext *context) override;

private:

};