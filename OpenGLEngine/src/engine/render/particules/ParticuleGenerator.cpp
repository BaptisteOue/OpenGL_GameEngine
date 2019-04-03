#include "ParticuleGenerator.h"


#pragma region Public API

ParticuleGenerator::ParticuleGenerator(int nbParticules)
	: m_NbParticules{ nbParticules }
{
	m_Positions.reserve(nbParticules);
	m_InitialVelocities.reserve(nbParticules);
}

ParticuleGenerator::~ParticuleGenerator()
{
}

void ParticuleGenerator::Init(const glm::vec3& center)
{
	GenerateParticules(center);
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
	return m_NbParticules;
}

void ParticuleGenerator::SetNbParticules(int value)
{
	m_NbParticules = value;
}

#pragma endregion


#pragma region Private API

void ParticuleGenerator::GenerateParticules(const glm::vec3& center)
{
	for (int i = 0; i < m_NbParticules; i++)
	{
		m_Positions.emplace_back(center);
		m_InitialVelocities.emplace_back(GenerateRandomConeSpeed());
		m_StartTimes.emplace_back(GenerateRandomStartTime());
	}
}

const glm::vec3 & ParticuleGenerator::GenerateRandomConeSpeed()
{
	glm::vec3 v;
	float random, velocity, theta, phi;

	random = ((float)rand()) / (float)RAND_MAX;
	theta = glm::mix(glm::radians(MIN_ANGLE), glm::radians(MAX_ANGLE), random);

	random = ((float)rand()) / (float)RAND_MAX;
	phi = glm::mix(0.0f, glm::radians(360.0f), random);

	v.x = sinf(theta) * cosf(phi);
	v.y = cosf(theta);
	v.z = sinf(theta) * sinf(phi);

	random = ((float)rand()) / (float)RAND_MAX;
	velocity = glm::mix(MIN_SPEED, MAX_SPEED, random);

	return glm::normalize(v) * velocity;
}

const float ParticuleGenerator::GenerateRandomStartTime()
{
	float random = ((float)rand()) / (float)RAND_MAX;
	return glm::mix(MIN_START_TIME, MAX_START_TIME, random);
}

#pragma endregion

