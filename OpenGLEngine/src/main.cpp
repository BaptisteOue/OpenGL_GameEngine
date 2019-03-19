#include "App.h"
#include "coreEngine/GameEngine.h"
#include "coreEngine/IGameLogic.h"
#include <stdio.h>

int main(void)
{

	IGameLogic* app = new App();
	GameEngine gameEngine("Test OpenGL", 1080, 720, *app);
	gameEngine.Start();
	
	delete app;

	return 0;
}