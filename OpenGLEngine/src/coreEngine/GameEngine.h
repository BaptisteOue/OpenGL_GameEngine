#pragma once

#include <thread>
#include "Timer.h"
#include "Window.h"
#include "IGameLogic.h"


class GameEngine
{
private:
    Window m_Window;
    Timer m_Timer;
    IGameLogic& m_GameLogic;
    std::thread m_Thread;

public:
	static float UPS;

private:
	void Init();
	void GameLoop();
	void CleanUp();

	void Input();
	void Update(float interval);
	void Render();

public:
    GameEngine(const char* title, int width, int height, IGameLogic& gameLogic);
    ~GameEngine();
    void Start();   
};