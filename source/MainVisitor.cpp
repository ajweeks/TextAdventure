
#include "MainVisitor.h"

using namespace antlrcpp;

MainVisitor::MainVisitor()
{
}

MainVisitor::~MainVisitor()
{
}

antlrcpp::Any MainVisitor::visitItem(textworldParser::ItemContext * context)
{
	std::cout << "Found item: " << context->ITEM()->getSymbol()->getText() << std::endl;
	std::cout << "Item name: " << context->ID()->getSymbol()->getText() << std::endl;

	return visitChildren(context);
}

antlrcpp::Any MainVisitor::visitAssignment(textworldParser::AssignmentContext * context)
{
	std::cout << "Found assignment" << std::endl;
	std::cout << "Property name: " << context->ID()->getSymbol()->getText() << std::endl;
	textworldParser::ValueContext* valueContext = context->value();
	if (valueContext->STRING() != nullptr)
	{
		std::cout << "Property value: " << valueContext->STRING()->getSymbol()->getText() << std::endl;
	}
	else if (valueContext->INT() != nullptr)
	{
		std::cout << "Property value: " << valueContext->INT()->getSymbol()->getText() << std::endl;
	}

	return visitChildren(context);
}
