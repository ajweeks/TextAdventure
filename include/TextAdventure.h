#pragma once

#include <vector>

class MainVisitor;

class TextAdventure
{
public:
	TextAdventure();

	void Run(const std::string& worldFilePath);
	
	static Globals gGlobals;

private:
	void PlayGame();
	void PopulateWordWhitelist();

	ParsedInput ParseInput(const std::string& input);
	void ApplyInput(ParsedInput& parsedInput);

	void PrintInvalidInputMessage(const ParsedInput& parsedInput);

	MainVisitor* m_Visitor;

	bool m_Playing;
	bool m_QuitMessage;
};
