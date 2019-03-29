#include "ParticuleGenerator.h"


#pragma region Public API

ParticuleGenerator::ParticuleGenerator(int nbParticules)
	: m_nbParticules{ nbParticules }
{
	m_Positions.reserve(100);
	m_InitialVelocities.reserve(100);
	GenerateParticules();
}

ParticuleGenerator::~ParticuleGenerator()
{
}

const std::vector<glm::vec3>& ParticuleGenerator::GetPositions() const
{
	return m_Positions;
}

const std::vector<glm::vec3>& ParticuleGenerator::GetInitialVelocities() const
{
	return m_InitialVelocities;
}

const std::vector<float>& ParticuleGenerator::GetStartTimes() const
{
	return m_StartTimes;
}

const int ParticuleGenerator::GetNbParticules() const
{
	return m_nbParticules;
}

#pragma endregion


#pragma region Private API

void ParticuleGenerator::GenerateParticules()
{
	for (int i = 0; i < m_nbParticules; i++)
	{
		m_Positions.emplace_back(0, 0, 0);
		m_InitialVelocities.emplace_back(GenerateRandomConeSpeed());
		m_StartTimes.emplace_back(GenerateRandomStartTime());
	}
}

const glm::vec3 & ParticuleGenerator::GenerateRandomConeSpeed()
{
	glm::vec3 v;
	float random, velocity, theta, phi;

	random = ((float)rand()) / (float)RAND_MAX;
	theta = glm::mix(0.0f, 3.14f / 6.0f, random);

	random = ((float)rand()) / (float)RAND_MAX;
	phi = glm::mix(0.0f, 3.14f * 2, random);

	v.x = sinf(theta) * cosf(phi);
	v.y = cosf(theta);
	v.z = sinf(theta) * sinf(phi);

	random = ((float)rand()) / (float)RAND_MAX;
	velocity = glm::mix(2.0f, 10.0f, random);

	return glm::normalize(v) * velocity;
}

const float ParticuleGenerator::GenerateRandomStartTime()
{
	float random = ((float)rand()) / (float)RAND_MAX;
	return glm::mix(0.0f, 5.0f, random);
}

#pragma endregion

