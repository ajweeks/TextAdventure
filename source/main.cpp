
// 2DAE1
// AJ Weeks

#include "stdafx.h"

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
	//_CrtSetBreakAlloc(594);
#endif

	TextAdventure* game = new TextAdventure();
	game->Run("resources/world1.w");

	delete game;

#if defined(DEBUG) || defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif 
}
