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
	m_MasterRenderer(),
	m_GameObjects(),
	m_ParticuleSystems()
{

}

App::~App()
{
		
}

void App::Init()
{
	m_Camera.Init();
	m_LightScene.Init();
	m_MasterRenderer.Init();

	Mesh plane{ Loader::LoadOBJ("./res/plane.obj") };
	Mesh bunny{ Loader::LoadOBJ("./res/bunny.obj") };
	Mesh dragon{ Loader::LoadOBJ("./res/dragon.obj") };
	Mesh cube{ Loader::LoadOBJ("./res/cube.obj") };
	Mesh sphere{ Loader::LoadOBJ("./res/sphere.obj") };

	Material material{ glm::vec3(0, 0.9f, 0.5f), glm::vec3(0, 0.9f, 0.5f), glm::vec3(1), 1.5, 150 };
	m_GameObjects.emplace_back(bunny, material, glm::vec3(0, 1, 20), glm::vec3(0), 4.0f);

	material.SetKa(glm::vec3(0, 0.5f, 0.9f));
	material.SetKd(glm::vec3(0, 0.5f, 0.9f));
	m_GameObjects.emplace_back(dragon, material, glm::vec3(0, -0.2f, -15), glm::vec3(0), 1.0f);

	material.SetReflectivity(0.1f);
	material.SetShineDamper(200);
	material.AddTexture(Loader::Load2DTexture("./res/brick.jpg"));
	m_GameObjects.emplace_back(plane, material, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 5.0f);

	material.AddTexture(Loader::Load2DTexture("./res/grass_grass_0052_01_preview.jpg"));
	material.SetReflectivity(0.0f);
	material.SetShineDamper(1);
	m_GameObjects.emplace_back(cube, material, glm::vec3(-20, 10, -20), glm::vec3(35, 17, 90), 2.0f);
	m_GameObjects.emplace_back(cube, material, glm::vec3(-20, 10, 20), glm::vec3(12, 47, 0), 2.0f);
	m_GameObjects.emplace_back(cube, material, glm::vec3(20, 5, 0), glm::vec3(63, -15, 123), 2.0f);
	m_GameObjects.emplace_back(cube, material, glm::vec3(10, 10, -25), glm::vec3(47, 20, 47), 2.0f);

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
}

void App::Render(float frameTime)
{
	m_MasterRenderer.Render(m_GameObjects, m_ParticuleSystems, m_LightScene, m_Camera, frameTime);
}

void App::CleanUp()
{
	for(auto& gameObject : m_GameObjects)
		gameObject.CleanUp();

	m_GameObjects.clear();
	m_LightScene.CleanUp();
	
	m_MasterRenderer.CleanUp();
}
