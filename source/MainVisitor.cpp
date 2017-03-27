
#include "MainVisitor.h"
#include "helpers.h"

using namespace antlrcpp;

MainVisitor::MainVisitor()
{
}

MainVisitor::~MainVisitor()
{
}

antlrcpp::Any MainVisitor::visitItem(textworldParser::ItemContext * context)
{
	std::cout << context->ITEM()->getSymbol()->getText() << std::endl;
	std::cout << context->ID()->getSymbol()->getText() << std::endl;
	std::cout << std::endl;

	return visitChildren(context);
}

antlrcpp::Any MainVisitor::visitAssignment(textworldParser::AssignmentContext * context)
{
	std::cout << context->ID()->getSymbol()->getText() << ":" << std::endl;
	textworldParser::ValueContext* valueContext = context->value();
	if (valueContext->STRING() != nullptr)
	{
		std::string str = valueContext->STRING()->getSymbol()->getText();

		RemoveCharFromString(str, '"');

		std::vector<std::string> strings;
		if (str.find("\n") != std::string::npos)
		{
			strings = Split(str);
		}

		if (strings.empty())
		{
			std::cout << str << std::endl;
		}
		else
		{
			for (size_t i = 0; i < strings.size(); i++)
			{
				std::cout << strings[i] << std::endl;
			}
		}
	}
	else if (valueContext->INT() != nullptr)
	{
		std::cout << valueContext->INT()->getSymbol()->getText() << std::endl;
	}

	std::cout << std::endl;

	return visitChildren(context);
}
