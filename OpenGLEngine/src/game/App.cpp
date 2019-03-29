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
	Material material{ glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 0.5f, 150 };
	
	m_GameObjects.emplace_back(bunny, material, glm::vec3(-10, 5, -10), glm::vec3(0), 4);
	m_GameObjects.emplace_back(dragon, material, glm::vec3(10, 5, -10), glm::vec3(0), 1);
	material.AddTexture(Loader::LoadTexture("./res/Abstract_Organic_002_COLOR.jpg"));
	m_GameObjects.emplace_back(plane, material, glm::vec3(0), glm::vec3(0), 10);


	ParticuleSystem particuleSystem1{};
	particuleSystem1.Init();
	particuleSystem1.SetCenter(glm::vec3(-20, 3, -10));
	particuleSystem1.SetGravityForce(glm::vec3(0, -4, 0));

	ParticuleSystem particuleSystem2{};
	particuleSystem2.Init();
	particuleSystem2.SetCenter(glm::vec3(0, 3, -10));
	particuleSystem2.SetGravityForce(glm::vec3(0, -8, 0));

	ParticuleSystem particuleSystem3{};
	particuleSystem3.Init();
	particuleSystem3.SetCenter(glm::vec3(20, 3, -10));
	particuleSystem3.SetGravityForce(glm::vec3(0, -16, 0));

	m_ParticuleSystems.push_back(particuleSystem1);
	m_ParticuleSystems.push_back(particuleSystem2);
	m_ParticuleSystems.push_back(particuleSystem3);

	//for (PointLight& p : m_LightScene.GetPointLights())
	//	m_GameObjects.push_back(p.GetLightObject());
	//for (SpotLight& s : m_LightScene.GetSpotLights())
	//	m_GameObjects.push_back(s.GetLightObject());
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
	m_GameObjectRenderer.Render(m_GameObjects, m_LightScene, m_Camera);
	m_ParticuleRenderer.Render(m_ParticuleSystems, m_Camera, frameTime);
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
