#include "App.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "../engine/render/models/Mesh.h"
#include "../engine/render/maths/Transformations.h"
#include "../engine/render/utils/Loader.h"

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

	m_GameObjectRenderer.Init();

	m_LightScene.Init();

	Material material1(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 1, 150);
	material1.AddTexture(Loader::LoadTexture("./res/Abstract_Organic_002_COLOR.jpg"));

	Material material2(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 1, 150);

	Material material3(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 1, 150);
	material3.AddTexture(Loader::LoadTexture("./res/Abstract_Organic_002_COLOR.jpg"));

	m_GameObjects.emplace_back(Mesh(Loader::LoadOBJ("./res/cube.obj")) , material1);
	m_GameObjects.emplace_back(Mesh(Loader::LoadOBJ("./res/cube.obj")) , material2, glm::vec3(-3, 0, 0));
	m_GameObjects.emplace_back(Mesh(Loader::LoadOBJ("./res/cube.obj")), material3, glm::vec3(3, 0, 0));
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
	for (GameObject& gameObject : m_GameObjects)
	{
		if (window.IsKeyPressed(GLFW_KEY_T))
		{
			float tessLevelOuter = gameObject.GetTessLevelOuter();
			gameObject.SetTessLevelOuter(tessLevelOuter + 0.1f);

		}
		else if (window.IsKeyPressed(GLFW_KEY_G))
		{
			float tessLevelOuter = gameObject.GetTessLevelOuter();
			gameObject.SetTessLevelOuter(tessLevelOuter - 0.1f);
		}
		if (window.IsKeyPressed(GLFW_KEY_Y))
		{
			float tessLevelInner = gameObject.GetTessLevelInner();
			gameObject.SetTessLevelInner(tessLevelInner + 0.1f);
		}
		else if (window.IsKeyPressed(GLFW_KEY_H))
		{
			float tessLevelInner = gameObject.GetTessLevelInner();
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
	m_LightScene.GetSpotLight().SimulateTorch(m_Camera);
}

void App::Render()
{
	m_GameObjectRenderer.Render(m_GameObjects, m_LightScene, m_Camera);
}

void App::CleanUp()
{
	for(GameObject& gameObject : m_GameObjects)
		gameObject.CleanUp();

	m_GameObjects.clear();
	m_LightScene.CleanUp();
	m_GameObjectRenderer.CleanUp();
}
