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
	m_GameObjects(),
	m_ParticuleSystems(),
	m_ParticuleRenderer()
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

	m_ParticuleRenderer.Init();

	Mesh plane{ Loader::LoadOBJ("./res/plane.obj") };
	Mesh bunny{ Loader::LoadOBJ("./res/bunny.obj") };
	Mesh dragon{ Loader::LoadOBJ("./res/dragon.obj") };

	Material material{ glm::vec3(0.9f, 0.7f, 0.4f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 1.5, 100 };
	m_GameObjects.emplace_back(bunny, material, glm::vec3(0, 1, 20), glm::vec3(0), 4);

	material.SetKa(glm::vec3(0.4f, 0.7f, 0.9f));
	m_GameObjects.emplace_back(dragon, material, glm::vec3(15, 0, -20), glm::vec3(0), 1);

	material.SetReflectivity(0.1f);
	material.SetShineDamper(200);
	material.AddTexture(Loader::LoadTexture("./res/brick.jpg"));
	m_GameObjects.emplace_back(plane, material, glm::vec3(0), glm::vec3(0), 5);
	m_GameObjects.emplace_back(plane, material, glm::vec3(0, 40, 0), glm::vec3(180, 0, 0), 5);
	m_GameObjects.emplace_back(plane, material, glm::vec3(0, 0, -40), glm::vec3(90, 0, 0), 5);
	m_GameObjects.emplace_back(plane, material, glm::vec3(0, 0, 40), glm::vec3(-90, 0, 0), 5);
	m_GameObjects.emplace_back(plane, material, glm::vec3(-40, 0, 0), glm::vec3(0, 0, -90), 5);
	m_GameObjects.emplace_back(plane, material, glm::vec3(40, 0, 0), glm::vec3(0, 0, 90), 5);


	ParticuleSystem particuleSystem1{ 100000 };
	particuleSystem1.SetCenter(glm::vec3(-15, 0, -20));
	particuleSystem1.SetAcceleration(glm::vec3(0, 25, 0));
	particuleSystem1.SetGravityForce(glm::vec3(0, -12.0f, 0));
	particuleSystem1.SetParticuleLifeTime(13.0f);				// TODO : Should be random per particule
	particuleSystem1.Init();

	m_ParticuleSystems.push_back(std::move(particuleSystem1));

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
}

void App::Render(float frameTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_GameObjectRenderer.Render(m_GameObjects, m_LightScene, m_Camera);
	m_ParticuleRenderer.Render(m_ParticuleSystems, m_LightScene, m_Camera, frameTime);
}

void App::CleanUp()
{
	for(auto& gameObject : m_GameObjects)
		gameObject.CleanUp();

	m_GameObjects.clear();
	m_LightScene.CleanUp();
	m_GameObjectRenderer.CleanUp();
	m_ParticuleRenderer.CleanUp();
}
