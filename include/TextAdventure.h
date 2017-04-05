#pragma once

#include "enums.h"
#include "structs.h"

#include <vector>

class MainVisitor;

class TextAdventure
{
public:
	TextAdventure();

	void Run(const std::string& worldFilePath);

private:
	void PlayGame();
	ApplyInputResult ApplyInput(World* world, const ParsedInput& parsedInput);
	ParsedInput ParseInput(const std::string& input);

	void PrintInvalidInputMessage(const ParsedInput& parsedInput, const ApplyInputResult& inputResult);
	std::string RemoveExtraWordsFromRemainingInput(std::string& remainingString);

	MainVisitor* m_Visitor;

};
