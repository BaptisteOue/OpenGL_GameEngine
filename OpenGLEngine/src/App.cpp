#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "App.h"
#include "models/Mesh.h"
#include "maths/Transformations.h"
#include "utils/OBJLoader.h"

App::App()
    : dCamera(0, 0, 0), 
	m_Camera(), 
	m_Mesh(), 
	m_ShaderProgram("./src/shaders/vertexShader.glsl", "./src/shaders/fragmentShader.glsl")
{

}

App::~App()
{

}

void App::Init()
{
    glClearColor(0.f, 0.0f, 0.0f, 1.0f);

    std::vector<GLfloat> positions = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    std::vector<GLfloat> colors = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    std::vector<GLubyte> indices = {
        0, 1, 2
    };

	m_Camera.Init();

	m_Mesh = OBJLoader::LoadOBJ("./res/monkey.obj");

    m_ShaderProgram.CreateShaderProgram();

	
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
}

void App::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_ShaderProgram.Use(true);
	
	glm::vec3 pos(0, 0, -2);
	glm::vec3 rotation(0, 0, 180.0f);
	float scale = 1;
	glm::mat4 modelMatrix = Transformations::GetModelMatrix(pos, rotation, scale);

	float FOV = 45.0f;
	float nearPlane = 0.01f;
	float farPlane = 1000.0f;
	glm::mat4 projectionMatrix = Transformations::GetProjectionMatrix(FOV, nearPlane, farPlane);

	glm::mat4 viewMatrix = Transformations::GetViewMatrix(m_Camera);

	m_ShaderProgram.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix);
    m_Mesh.Draw();
	m_ShaderProgram.Use(false);
}

void App::CleanUp()
{
	m_Mesh.CleanUp();
}
