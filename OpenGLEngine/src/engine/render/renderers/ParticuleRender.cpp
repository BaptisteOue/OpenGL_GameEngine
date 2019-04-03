#include "ParticuleRender.h"
#include "../maths/Transformations.h"
#include <iostream>

ParticuleRender::ParticuleRender()
	: m_ParticuleShader(), m_ParticuleFeedForwardShader()
{

}

ParticuleRender::~ParticuleRender()
{

}

void ParticuleRender::Init()
{
	m_ParticuleShader.CreateShaderProgram();
	m_ParticuleFeedForwardShader.CreateShaderProgram();
}

void ParticuleRender::Render(std::vector<ParticuleSystem> & particuleSystems, LightScene& lightScene, Camera& camera, float frameTime)
{

	glm::mat4 projectionMatrix{ Transformations::GetProjectionMatrix(FOV, nearPlane, farPlane) };
	glm::mat4 viewMatrix{ Transformations::GetViewMatrix(camera) };
	glm::mat4 modelMatrix{ Transformations::GetModelMatrix(glm::vec3{0}, glm::vec3{0}, glm::vec3{1}) };

	for (ParticuleSystem& particuleSystem : particuleSystems)
	{
		// Compute phase for transformation feedback
		m_ParticuleFeedForwardShader.Use(true);
		m_ParticuleFeedForwardShader.LoadLifeTimeUniform(particuleSystem.GetParticuleLifetime());
		m_ParticuleFeedForwardShader.LoadSimulationTimeUniform(particuleSystem.GetSimulationTime());
		m_ParticuleFeedForwardShader.LoadAccelerationUniform(particuleSystem.GetAcceleration());
		m_ParticuleFeedForwardShader.LoadGravityForceUniform(particuleSystem.GetGravityForce());
		m_ParticuleFeedForwardShader.LoadFrameTimeUniform(frameTime);
		m_ParticuleFeedForwardShader.LoadCenterUniform(particuleSystem.GetCenter());
		particuleSystem.GetParticuleGroup().UpdatePass();
		m_ParticuleFeedForwardShader.Use(false);

		// Draw phase
		m_ParticuleShader.Use(true);
		m_ParticuleShader.LoadLifeTimeUniform(particuleSystem.GetParticuleLifetime());
		m_ParticuleShader.LoadSimulationTimeUniform(particuleSystem.GetSimulationTime());
		m_ParticuleShader.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix);
		m_ParticuleShader.LoadLightsUniforms(lightScene, viewMatrix);
		particuleSystem.GetParticuleGroup().RenderPass();
		m_ParticuleShader.Use(false);
	}
}

void ParticuleRender::CleanUp()
{
	m_ParticuleShader.CleanUp();
}
