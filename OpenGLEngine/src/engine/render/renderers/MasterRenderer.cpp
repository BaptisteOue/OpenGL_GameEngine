#include "MasterRenderer.h"
#include <iostream>
#include "../maths/Transformations.h"

MasterRenderer::MasterRenderer()
	: m_GameObjectRender(),
	m_ParticuleRender(),
	m_TestFrameBuffer(1080, 720),
	m_TestFBOShader("./src/engine/render/shaders/src/vertexShaderTestFBO.glsl",
					"./src/engine/render/shaders/src/fragmentShaderTestFBO.glsl")
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Init()
{
	m_GameObjectRender.Init();
	m_ParticuleRender.Init();

	m_TestFBOShader.CreateShaderProgram();

	m_TestFrameBuffer.Init();
	m_TestFrameBuffer.AddTexture2DColorAttachement();
	m_TestFrameBuffer.AddRBODepthStencilAttachement();
	if(!m_TestFrameBuffer.BindAttachements())
		std::cout << "Failed to create FrameBuffer." << std::endl;

	float quadVertices[] = { 
		// positions   // texCoords
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 -1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_QuadVAO);
	glBindVertexArray(m_QuadVAO);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void MasterRenderer::Render(std::vector<GameObject>& gameObjects,
							std::vector<ParticuleSystem>& particuleSystems,
							LightScene & lightScene, 
							Camera & camera, 
							float frameTime)
{

	m_TestFrameBuffer.Bind(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_GameObjectRender.Render(gameObjects, lightScene, camera);
	m_ParticuleRender.Render(particuleSystems, lightScene, camera, frameTime);
	m_TestFrameBuffer.Bind(false);

	glClear(GL_COLOR_BUFFER_BIT);
	m_TestFBOShader.Use(true);
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(m_QuadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TestFrameBuffer.GetColorTexture());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glEnable(GL_DEPTH_TEST);
	m_TestFBOShader.Use(false);
	
}

void MasterRenderer::CleanUp()
{
	m_GameObjectRender.CleanUp();
	m_ParticuleRender.CleanUp();
	
	m_TestFrameBuffer.CleanUp();
	m_TestFBOShader.CleanUp();
}