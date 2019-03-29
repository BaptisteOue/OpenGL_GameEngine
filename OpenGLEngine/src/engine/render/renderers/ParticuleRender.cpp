#include "ParticuleRender.h"
#include "../maths/Transformations.h"

ParticuleRender::ParticuleRender()
	: m_ParticuleShader(), m_ParticuleFeedForwardShader()
{

}

ParticuleRender::~ParticuleRender()
{

}

void ParticuleRender::Init()
{
	m_ParticuleFeedForwardShader.CreateShaderProgram();
	m_ParticuleShader.CreateShaderProgram();
}

void ParticuleRender::Render(std::vector<ParticuleSystem> & particuleSystems, Camera& camera, float frameTime)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (ParticuleSystem& particuleSystem : particuleSystems)
	{
		// Compute phase for transformation feedback
		m_ParticuleFeedForwardShader.Use(true);
		m_ParticuleFeedForwardShader.LoadLifeTimeUniform(particuleSystem.GetParticuleLifetime());
		m_ParticuleFeedForwardShader.LoadSimulationTimeUniform(particuleSystem.GetSimulationTime());
		m_ParticuleFeedForwardShader.LoadAccelerationUniform(particuleSystem.GetAcceleration());
		m_ParticuleFeedForwardShader.LoadGravityForceUniform(particuleSystem.GetGravityForce());
		m_ParticuleFeedForwardShader.LoadFrameTimeUniform(frameTime);
		particuleSystem.GetParticuleGroup().UpdatePass();
		m_ParticuleFeedForwardShader.Use(false);

		// Draw phase
		glm::mat4 projectionMatrix{ Transformations::GetProjectionMatrix(FOV, nearPlane, farPlane) };
		glm::mat4 viewMatrix{ Transformations::GetViewMatrix(camera) };
		glm::mat4 modelMatrix{ Transformations::GetModelMatrix(particuleSystem.GetCenter(), glm::vec3{0}, glm::vec3{1}) };

		m_ParticuleShader.Use(true);
		m_ParticuleShader.LoadLifeTimeUniform(particuleSystem.GetParticuleLifetime());
		m_ParticuleShader.LoadSimulationTimeUniform(particuleSystem.GetSimulationTime());
		m_ParticuleShader.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix);
		m_ParticuleShader.LoadCameraPosUniform(camera.GetPos());
		m_ParticuleShader.LoadMaxPointSizeUniform(30);
		particuleSystem.GetParticuleGroup().RenderPass();
		m_ParticuleShader.Use(false);
	}
}

void ParticuleRender::CleanUp()
{
	m_ParticuleShader.CleanUp();
}
