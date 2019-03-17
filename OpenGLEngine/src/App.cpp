#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include "App.h"
#include "models/Mesh.h"
#include "maths/Transformations.h"
#include "utils/OBJLoader.h"

App::App()
    : dCamera(0, 0, 0), m_Camera(), m_Mesh(), m_TessShader()
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

	m_Camera.Init();

	m_Material = new Material(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 1, 100);
	m_DirecationalLight = new DirectionalLight(glm::vec4(0.7, 0.6, 0.9, 1), glm::vec4(-1,-1, -1, 0));
	m_Mesh = OBJLoader::LoadOBJ("./res/dragon.obj");
	//m_Mesh.LoadMesh(positions, normals, indices);
    m_TessShader.CreateShaderProgram();
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
		float tessLevelOuter = m_Mesh.GetTessLevelOuter();
		m_Mesh.SetTessLevelOuter(tessLevelOuter + 0.1f);

	}
	else if (window.IsKeyPressed(GLFW_KEY_G))
	{
		float tessLevelOuter = m_Mesh.GetTessLevelOuter();
		m_Mesh.SetTessLevelOuter(tessLevelOuter - 0.1f);
	}
	if (window.IsKeyPressed(GLFW_KEY_Y))
	{
		float tessLevelInner = m_Mesh.GetTessLevelInner();
		m_Mesh.SetTessLevelInner(tessLevelInner + 0.1f);
	}
	else if (window.IsKeyPressed(GLFW_KEY_H))
	{
		float tessLevelInner = m_Mesh.GetTessLevelInner();
		m_Mesh.SetTessLevelInner(tessLevelInner - 0.1f);
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

	m_TessShader.LoadTessLevels(m_Mesh.GetTessLevelOuter(), m_Mesh.GetTessLevelInner());
	m_TessShader.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix);
	m_TessShader.LoadLightsUniforms(*m_DirecationalLight, viewMatrix);
	m_TessShader.LoadMaterialUniforms(*m_Material);

    m_Mesh.Draw();
	m_TessShader.Use(false);
}

void App::CleanUp()
{
	m_Mesh.CleanUp();
	delete m_DirecationalLight;
	delete m_Material;
}
