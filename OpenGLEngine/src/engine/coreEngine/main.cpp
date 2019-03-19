#include "../../game/App.h"
#include "../render/core/RenderEngine.h"
#include "../render/core/IGameLogic.h"

int main(void)
{

	IGameLogic* app = new App();
	RenderEngine renderEngine("Test OpenGL", 1080, 720, *app);
	renderEngine.Start();
	
	delete app;

	return 0;
}