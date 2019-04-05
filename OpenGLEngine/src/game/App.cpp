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

	Material material{ glm::vec3(0, 0.9f, 0.5f), glm::vec3(0, 0.9f, 0.5f), glm::vec3(1), 1.5, 150 };
	m_GameObjects.emplace_back(bunny, material, glm::vec3(0, 1, 20), glm::vec3(0), 4);

	material.SetKa(glm::vec3(0, 0.5f, 0.9f));
	material.SetKd(glm::vec3(0, 0.5f, 0.9f));
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

	Material particuleMaterial1{ glm::vec3(0.9f, 0.3f, 0.3f), glm::vec3(0.9f, 0.3f, 0.3f), glm::vec3(1), 2, 200 };
	ParticuleSystem particuleSystem1{ 1000 };
	particuleSystem1.SetMaterial(particuleMaterial1);
	particuleSystem1.SetCenter(glm::vec3(-20, 0, -20));
	particuleSystem1.SetAcceleration(glm::vec3(0, 15, 0));
	particuleSystem1.SetGravityForce(glm::vec3(0, -12.0f, 0));
	particuleSystem1.SetParticuleLifeTime(13.0f);				// TODO : Should be random per particule
	particuleSystem1.Init();

	Material particuleMaterial2{ glm::vec3(0.3f, 0.9f, 0.3f), glm::vec3(0.3f, 0.9f, 0.3f), glm::vec3(1), 2, 200 };
	ParticuleSystem particuleSystem2{ 1000 };
	particuleSystem2.SetMaterial(particuleMaterial2);
	particuleSystem2.SetCenter(glm::vec3(20, 0, 20));
	particuleSystem2.SetAcceleration(glm::vec3(0, 15, 0));
	particuleSystem2.SetGravityForce(glm::vec3(0, -12.0f, 0));
	particuleSystem2.SetParticuleLifeTime(13.0f);				// TODO : Should be random per particule
	particuleSystem2.Init();

	Material particuleMaterial3{ glm::vec3(0.3f, 0.3f, 0.9f), glm::vec3(0.3f, 0.3f, 0.9f), glm::vec3(1), 2, 200 };
	ParticuleSystem particuleSystem3{ 1000 };
	particuleSystem3.SetMaterial(particuleMaterial3);
	particuleSystem3.SetCenter(glm::vec3(-20, 0, 20));
	particuleSystem3.SetAcceleration(glm::vec3(0, 15, 0));
	particuleSystem3.SetGravityForce(glm::vec3(0, -12.0f, 0));
	particuleSystem3.SetParticuleLifeTime(13.0f);				// TODO : Should be random per particule
	particuleSystem3.Init();

	m_ParticuleSystems.push_back(std::move(particuleSystem1));
	m_ParticuleSystems.push_back(std::move(particuleSystem2));
	m_ParticuleSystems.push_back(std::move(particuleSystem3));

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
