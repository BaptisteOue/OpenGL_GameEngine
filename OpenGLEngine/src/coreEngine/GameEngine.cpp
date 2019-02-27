#include <thread>
#include "GameEngine.h"
#include "Timer.h"

float GameEngine::UPS = 60;

GameEngine::GameEngine(const char* Title, int Width, int Height, IGameLogic& GameLogic)
    : m_Window(Width, Height, Title), m_GameLogic(GameLogic), m_Timer(), m_Thread()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::Start()
{
    m_Thread = std::thread(&GameEngine::Init, this);
	m_Thread.join();
}

void GameEngine::Init()
{
    m_Window.Init();
	m_Timer.Init();
    m_GameLogic.Init();

    GameLoop();
}

void GameEngine::GameLoop()
{

    float elapsedTime = 0;
    float lag = 0;

    float msPerUpdate = GameEngine::UPS / 1000.0f;
    
    while(!m_Window.ShouldClose())
    {
		m_Timer.PrintFPS();

        elapsedTime = m_Timer.GetElapsedTime();
		lag += elapsedTime;

        Input();

        while(lag >= msPerUpdate) 
        {
            Update(msPerUpdate);
            lag -= msPerUpdate;
        }

        Render();
    }

    CleanUp();
}

void GameEngine::CleanUp()
{
    m_GameLogic.CleanUp();
    m_Window.CleanUp();
}

void GameEngine::Input()
{
    if(m_Window.IsKeyPressed(GLFW_KEY_ESCAPE))
        Window::s_ShouldClose = true;
}

void GameEngine::Update(float Interval)
{
    m_GameLogic.Update(Interval);
}

void GameEngine::Render()
{
    m_GameLogic.Render();
    m_Window.Update();
}
