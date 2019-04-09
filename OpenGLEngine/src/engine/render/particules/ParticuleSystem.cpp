#include "ParticuleSystem.h"


#pragma region Public API

ParticuleSystem::ParticuleSystem(int nbParticules,
	glm::vec3 center,
	glm::vec3 gravityForce,
	glm::vec3 acceleration,
	float lifeTime,
	const Material& material)
	: m_ParticuleGenerator(nbParticules),
	m_Center{ center },
	m_GravityForce{ gravityForce },
	m_Acceleration{acceleration},
	m_ParticuleLifetime{ lifeTime },
	m_NbParticules{ nbParticules },
	m_Material{material}
{
}

ParticuleSystem::~ParticuleSystem()
{
}

void ParticuleSystem::Create()
{
	// Generate particules
	m_ParticuleGenerator.Init();

	m_StartedTime = std::chrono::high_resolution_clock::now();

	const std::vector<glm::vec3>& particulePos = m_ParticuleGenerator.GetPositions();
	const std::vector<glm::vec3>& particuleSpeeds = m_ParticuleGenerator.GetInitialVelocities();

	std::vector<GLfloat> pos;
	pos.reserve(m_NbParticules * 3);

	std::vector<GLfloat> speeds;
	pos.reserve(m_NbParticules * 3);

	// Fill pos, velocity and startime buffers
	for (int i = 0; i < m_NbParticules; i++)
	{
		pos.push_back(particulePos[i].x);
		pos.push_back(particulePos[i].y);
		pos.push_back(particulePos[i].z);

		speeds.push_back(particuleSpeeds[i].x);
		speeds.push_back(particuleSpeeds[i].y);
		speeds.push_back(particuleSpeeds[i].z);
	}

	// Load thr "particule group mesh"
	m_ParticuleGroup.SetNbParticules(m_NbParticules);
	m_ParticuleGroup.LoadParticuleGroup(pos, speeds, m_ParticuleGenerator.GetStartTimes());
}

const glm::vec3 & ParticuleSystem::GetCenter() const
{
	return m_Center;
}

const glm::vec3 & ParticuleSystem::GetGravityForce() const
{
	return m_GravityForce;
}

const glm::vec3 & ParticuleSystem::GetAcceleration() const
{
	return m_Acceleration;
}

float ParticuleSystem::GetSimulationTime() const
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> time = currentTime - m_StartedTime;

	return time.count();
}

float ParticuleSystem::GetParticuleLifetime() const
{
	return m_ParticuleLifetime;
}

ParticuleGroup & ParticuleSystem::GetParticuleGroup()
{
	return m_ParticuleGroup;
}

const Material & ParticuleSystem::GetMaterial() const
{
	return m_Material;
}

Material & ParticuleSystem::GetMaterial()
{
	return m_Material;
}

void ParticuleSystem::SetCenter(const glm::vec3& value)
{
	m_Center = value;
}

void ParticuleSystem::SetGravityForce(const glm::vec3& value)
{
	m_GravityForce = value;
}

void ParticuleSystem::SetAcceleration(const glm::vec3& value)
{
	m_Acceleration = value;
}

void ParticuleSystem::SetParticuleLifeTime(const float value)
{
	m_ParticuleLifetime = value;
}

void ParticuleSystem::SetMaterial(const Material & value)
{
	m_Material = value;
}

#pragma endregion

