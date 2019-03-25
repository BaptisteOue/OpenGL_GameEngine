#pragma once

#include <thread>
#include "Timer.h"
#include "Window.h"
#include "IGameLogic.h"


class RenderEngine
{
private:
    Window m_Window;
    Timer m_Timer;
    IGameLogic& m_GameLogic;
    std::thread m_Thread;

public:
	static constexpr auto UPS = 60;

private:
	void Init();
	void GameLoop();
	void CleanUp();

	void Input();
	void Update(float interval);
	void Render();

public:
	RenderEngine(const char* title, int width, int height, IGameLogic& gameLogic);
    ~RenderEngine();
    void Start();   
};