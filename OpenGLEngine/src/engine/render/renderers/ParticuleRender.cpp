#include "ParticuleRender.h"
#include "../maths/Transformations.h"

ParticuleRender::ParticuleRender()
	: m_ParticuleShader()
{

}

ParticuleRender::~ParticuleRender()
{

}

void ParticuleRender::Init()
{
	m_ParticuleShader.CreateShaderProgram();
}

void ParticuleRender::Render(ParticuleSystem & particuleSystem, Camera& camera)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Compute phase (In coming with transform feedback)

	// Draw phase
	glm::mat4 projectionMatrix{ Transformations::GetProjectionMatrix(FOV, nearPlane, farPlane) };
	glm::mat4 viewMatrix{ Transformations::GetViewMatrix(camera) };
	glm::mat4 modelMatrix{ Transformations::GetModelMatrix(particuleSystem.GetCenter(), glm::vec3{0}, glm::vec3{1})};

	m_ParticuleShader.Use(true);
	m_ParticuleShader.LoadGravityForceUniform(particuleSystem.GetGravityForce());
	m_ParticuleShader.LoadLifeTimeUniform(particuleSystem.GetParticuleLifetime());
	m_ParticuleShader.LoadSimulationTimeUniform(particuleSystem.GetSimulationTime());
	m_ParticuleShader.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix);
	particuleSystem.GetParticuleGroup().Draw();
	m_ParticuleShader.Use(false);
}

void ParticuleRender::CleanUp()
{
	m_ParticuleShader.CleanUp();
}
