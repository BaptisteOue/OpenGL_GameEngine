#include "RenderEngine.h"


#pragma region Public API

RenderEngine::RenderEngine(const char* Title, int Width, int Height, IGameLogic& GameLogic)
    : m_Window(Width, Height, Title), m_GameLogic(GameLogic), m_Timer(), m_Thread()
{
}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::Start()
{
    m_Thread = std::thread(&RenderEngine::Init, this);
	m_Thread.join();
}

void RenderEngine::Init()
{
    m_Window.Init();
	m_Timer.Init();
    m_GameLogic.Init();

    GameLoop();
}

void RenderEngine::GameLoop()
{
	float elapsedTime = 0;
    float lag = 0;

    float msPerUpdate = RenderEngine::UPS / 1000.0f;
    
    while(!m_Window.ShouldClose())
    {
        elapsedTime = m_Timer.GetElapsedTime();
		lag += elapsedTime;

        Input();

        while(lag >= msPerUpdate) 
        {
            Update(msPerUpdate);
            lag -= msPerUpdate;
        }

        Render(elapsedTime);
    }

    CleanUp();
}

#pragma endregion

#pragma region Private API
void RenderEngine::CleanUp()
{
    m_GameLogic.CleanUp();
    m_Window.CleanUp();
}

void RenderEngine::Input()
{
    if(m_Window.IsKeyPressed(GLFW_KEY_ESCAPE))
        Window::s_ShouldClose = true;
	if (m_Window.IsKeyPressed(GLFW_KEY_C))
		m_Timer.LogFPS(true);
	if (m_Window.IsKeyPressed(GLFW_KEY_X))
		m_Timer.LogFPS(false);

	m_GameLogic.Input(m_Window);
}

void RenderEngine::Update(float interval)
{
	m_Timer.Update();
    m_GameLogic.Update(interval);
}

void RenderEngine::Render(float frameTime)
{
    m_GameLogic.Render(frameTime);
    m_Window.Update();
}

#pragma endregion