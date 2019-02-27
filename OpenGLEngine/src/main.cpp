#include "coreEngine/IGameLogic.h"
#include "coreEngine/GameEngine.h"
#include "App.h"

int main(void)
{
	IGameLogic* app = new App();
	GameEngine gameEngine("Test OpenGL", 1080, 720, *app);
	gameEngine.Start();
	
	return 0;
}