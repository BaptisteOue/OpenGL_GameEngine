#include "SkyboxRenderer.h"
#include "../utils/Loader.h"
#include "../maths/Transformations.h"
#include "./MasterRenderer.h"

SkyboxRenderer::SkyboxRenderer()
	: m_SkyboxShader{},
	m_CubeMap{},
	m_CubeMesh{}
{
}

SkyboxRenderer::~SkyboxRenderer()
{
}

void SkyboxRenderer::Init()
{
	m_SkyboxShader.CreateShaderProgram();
	m_CubeMap = Loader::LoadCubeMapTexture(TEXTURES);
	m_CubeMesh = Loader::LoadOBJ("./res/cube.obj");
}

void SkyboxRenderer::Render(Camera& camera)
{
	glm::mat4 projectionMatrix(Transformations::GetProjectionMatrix(MasterRenderer::FOV, MasterRenderer::nearPlane, MasterRenderer::farPlane));
	glm::mat4 viewMatrix(glm::mat3(Transformations::GetViewMatrix(camera)));
	m_SkyboxShader.Use(true);
	m_SkyboxShader.LoadMatricesUniforms(viewMatrix, projectionMatrix);
	glActiveTexture(m_CubeMap.GetActiveTexture());
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMap.GetTextureID());
	m_CubeMesh.Draw();
	m_SkyboxShader.Use(false);
}

void SkyboxRenderer::CleanUp()
{
	m_CubeMesh.CleanUp();
	m_SkyboxShader.CleanUp();
}