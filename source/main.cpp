
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
#if defined(DEBUG) || defined(_DEBUG)
	//_CrtSetBreakAlloc(18);
#endif

	TextAdventure* game = new TextAdventure();

	const std::string worldFilePath = argv[1];
	game->Run(worldFilePath);

#if defined(DEBUG) || defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif 

	delete game;
}
