#include "App.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "../engine/render/models/Mesh.h"
#include "../engine/render/maths/Transformations.h"
#include "../engine/render/utils/Loader.h"
#include <chrono>

App::App()
    : dCamera(0, 0, 0),
	m_Camera(),
	m_LightScene(),
	m_GameObjectRenderer(),
	m_GameObjects()
{

}

App::~App()
{
		
}

void App::Init()
{
	m_Camera.Init();

	m_LightScene.Init();

	m_GameObjectRenderer.Init();

	Mesh mesh{ Loader::LoadOBJ("./res/cube.obj") };
	Material material{ glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 0.8f, 100 };

	for (int i = -10; i < 10; i++)
	{
		for (int j = -10; j < 10; j++)
		{
			m_GameObjects.emplace_back(mesh, material, glm::vec3(-2.5f * i, 0, -2.5f * j));
		}
	}
}

void App::Input(Window& window)
{
	dCamera = glm::vec3(0, 0, 0);

	if (window.IsKeyPressed(GLFW_KEY_W))
	{
		dCamera.z -= 1;
	}
	else if (window.IsKeyPressed(GLFW_KEY_S))
	{
		dCamera.z += 1;
	}

	if (window.IsKeyPressed(GLFW_KEY_A))
	{
		dCamera.x -= 1;
	}
	else if (window.IsKeyPressed(GLFW_KEY_D))
	{
		dCamera.x += 1;
	}

	if (window.IsKeyPressed(GLFW_KEY_SPACE))
	{
		dCamera.y += 1;
	}
	else if (window.IsKeyPressed(GLFW_KEY_TAB))
	{
		dCamera.y -= 1;
	}

	if (window.IsKeyPressed(GLFW_KEY_L))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (window.IsKeyPressed(GLFW_KEY_F))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Tesselation levels
	for (auto& gameObject : m_GameObjects)
	{
		if (window.IsKeyPressed(GLFW_KEY_T))
		{
			auto tessLevelOuter = gameObject.GetTessLevelOuter();
			gameObject.SetTessLevelOuter(tessLevelOuter + 0.1f);

		}
		else if (window.IsKeyPressed(GLFW_KEY_G))
		{
			auto tessLevelOuter = gameObject.GetTessLevelOuter();
			gameObject.SetTessLevelOuter(tessLevelOuter - 0.1f);
		}
		if (window.IsKeyPressed(GLFW_KEY_Y))
		{
			auto tessLevelInner = gameObject.GetTessLevelInner();
			gameObject.SetTessLevelInner(tessLevelInner + 0.1f);
		}
		else if (window.IsKeyPressed(GLFW_KEY_H))
		{
			auto tessLevelInner = gameObject.GetTessLevelInner();
			gameObject.SetTessLevelInner(tessLevelInner - 0.1f);
		}
	}
	

	if (Window::s_MouseMooved)
	{
		m_Camera.SetCurrentMouseX(Window::s_CurrentX);
		m_Camera.SetCurrentMouseY(Window::s_CurrentY);
		Window::s_MouseMooved = false;
	}
}

void App::Update(float interval)
{
	m_Camera.Update(dCamera);
	if(m_LightScene.GetSpotLights().size() > 0)
		m_LightScene.GetTorch().SimulateTorch(m_Camera);

	static float time = 0;
	time += interval;

	for (auto& gameObject : m_GameObjects)
	{
		auto scale = gameObject.GetScale();
		auto position = gameObject.GetPosition();

		auto d = glm::distance(glm::vec2(0, 0), glm::vec2(position.x, position.z));
		auto offset = d;
		scale.y += cos(-time * 3 + offset/4.0f) * 1;
		if (scale.y <= 0.5f)
			scale.y = 0.5f;
		gameObject.SetScale(scale);
	}
}

void App::Render()
{
	m_GameObjectRenderer.Render(m_GameObjects, m_LightScene, m_Camera);
}

void App::CleanUp()
{
	for(auto& gameObject : m_GameObjects)
		gameObject.CleanUp();

	m_GameObjects.clear();
	m_LightScene.CleanUp();
	m_GameObjectRenderer.CleanUp();
}
