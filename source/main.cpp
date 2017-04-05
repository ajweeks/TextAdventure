
// 2DAE1
// AJ Weeks

#include "TextAdventure.h"

#include <string>

#if defined(DEBUG) || defined(_DEBUG)
	// Memory leak detection
	#define _CRTDBG_MAP_ALLOC  
	#include <stdlib.h>  
	#include <crtdbg.h>  
#endif

int main(int argc, const char* argv[])
{
	//_CrtSetBreakAlloc(18);

	TextAdventure* game = new TextAdventure();

	const std::string worldFilePath = argv[1];
	game->Run(worldFilePath);

	_CrtDumpMemoryLeaks();
	
	delete game;
}
