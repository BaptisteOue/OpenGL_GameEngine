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
	m_Camera()
{

}

App::~App()
{
		
}

void App::Init()
{
    std::vector<GLfloat> positions = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    std::vector<GLfloat> normals = {
		0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    std::vector<GLuint> indices = {
        0, 1, 2
    };

	m_TessShader.CreateShaderProgram();

	m_Camera.Init();

	Mesh mesh(Loader::LoadOBJ("./res/bunny.obj"));
	Material material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 1, 150);
	material.AddTexture(Loader::LoadTexture("./res/Abstract_Organic_002_COLOR.jpg"));
	m_GameObject = new GameObject(mesh, material);

	m_DirecationalLight = new DirectionalLight(glm::vec3(0.2), glm::vec3(-1, -1, -1));
	m_PointLight = new PointLight(glm::vec3(0, 0.4f, 0.7f), glm::vec3(0, 1.5f, 3));
	m_PointLight->SetAttenuation(1, 0.2f, 0.02f);
	m_SpotLight = new SpotLight(*m_PointLight, 10, glm::vec3(0, 0, -1));

	m_PointLight->SetPosition(glm::vec3(2, 2, 0));
	m_PointLight->SetColor(glm::vec3(1, 0, 0));
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
	if (window.IsKeyPressed(GLFW_KEY_T))
	{
		float tessLevelOuter = m_GameObject->GetTessLevelOuter();
		m_GameObject->SetTessLevelOuter(tessLevelOuter + 0.1f);

	}
	else if (window.IsKeyPressed(GLFW_KEY_G))
	{
		float tessLevelOuter = m_GameObject->GetTessLevelOuter();
		m_GameObject->SetTessLevelOuter(tessLevelOuter - 0.1f);
	}
	if (window.IsKeyPressed(GLFW_KEY_Y))
	{
		float tessLevelInner = m_GameObject->GetTessLevelInner();
		m_GameObject->SetTessLevelInner(tessLevelInner + 0.1f);
	}
	else if (window.IsKeyPressed(GLFW_KEY_H))
	{
		float tessLevelInner = m_GameObject->GetTessLevelInner();
		m_GameObject->SetTessLevelInner(tessLevelInner - 0.1f);
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
	m_SpotLight->SetPosition(m_Camera.GetPos());
	m_SpotLight->SetDirection(m_Camera.GetFront());
}

void App::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_TessShader.Use(true);

	glm::vec3 pos(0, 0, -2);
	glm::vec3 rotation(0, 0, 0);
	float scale = 1;
	glm::mat4 modelMatrix = Transformations::GetModelMatrix(pos, rotation, scale);

	float FOV = 45.0f;
	float nearPlane = 0.01f;
	float farPlane = 1000.0f;
	glm::mat4 projectionMatrix = Transformations::GetProjectionMatrix(FOV, nearPlane, farPlane);

	glm::mat4 viewMatrix = Transformations::GetViewMatrix(m_Camera);

	if (m_GameObject->GetMaterial().IsTextured())
	{
		glActiveTexture(m_GameObject->GetMaterial().GetTexture().GetActiveTexture());
		glBindTexture(GL_TEXTURE_2D, m_GameObject->GetMaterial().GetTexture().GetTextureID());
	}
		
	m_TessShader.LoadTessLevels(m_GameObject->GetTessLevelOuter(), m_GameObject->GetTessLevelInner());
	m_TessShader.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix);
	m_TessShader.LoadLightsUniforms(*m_DirecationalLight, *m_PointLight, *m_SpotLight, viewMatrix);
	m_TessShader.LoadMaterialUniforms(m_GameObject->GetMaterial());

	m_GameObject->Draw();
	m_TessShader.Use(false);
}

void App::CleanUp()
{
	m_GameObject->CleanUp();
	delete m_DirecationalLight;
	delete m_PointLight;
	delete m_GameObject;
}
