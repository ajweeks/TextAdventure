
#include "antlr4-runtime.h"
#include "textworldLexer.h"
#include "textworldParser.h"
#include "textworldBaseListener.h"
#include "textworldBaseVisitor.h"
#include "MainVisitor.h"

#include <iostream>
#include <Windows.h>

using namespace antlr4;

int main(int argc, const char* argv[])
{
	std::ifstream stream;
	stream.open(argv[1]);
	if (stream.is_open())
	{
		ANTLRInputStream input(stream);
		textworldLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		textworldParser parser(&tokens);

		tree::ParseTree* tree = parser.world();

		textworldVisitor* visitor = new MainVisitor();

		visitor->visit(tree);

		getchar();
	}
}