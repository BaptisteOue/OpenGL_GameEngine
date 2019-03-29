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
	GenerateParticules(center, ParticuleGenerator::MIN_ANGLE, ParticuleGenerator::MAX_ANGLE, ParticuleGenerator::MIN_SPEED, ParticuleGenerator::MAX_SPEED);
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

void ParticuleGenerator::GenerateParticules(const glm::vec3& center, float minAngle, float maxAngle, float minSpeed, float maxSpeed)
{
	for (int i = 0; i < m_NbParticules; i++)
	{
		m_Positions.emplace_back(center);
		m_InitialVelocities.emplace_back(GenerateRandomConeSpeed(minAngle, maxAngle, minSpeed, maxSpeed));
		m_StartTimes.emplace_back(GenerateRandomStartTime());
	}
}

const glm::vec3 & ParticuleGenerator::GenerateRandomConeSpeed(float minAngle, float maxAngle, float minSpeed, float maxSpeed)
{
	glm::vec3 v;
	float random, velocity, theta, phi;

	random = ((float)rand()) / (float)RAND_MAX;
	theta = glm::mix(glm::radians(minAngle), glm::radians(maxAngle), random);

	random = ((float)rand()) / (float)RAND_MAX;
	phi = glm::mix(0.0f, glm::radians(360.0f), random);

	v.x = sinf(theta) * cosf(phi);
	v.y = cosf(theta);
	v.z = sinf(theta) * sinf(phi);

	random = ((float)rand()) / (float)RAND_MAX;
	velocity = glm::mix(minSpeed, maxSpeed, random);

	return glm::normalize(v) * velocity;
}

const float ParticuleGenerator::GenerateRandomStartTime()
{
	float random = ((float)rand()) / (float)RAND_MAX;
	return glm::mix(0.0f, 7.0f, random);
}

#pragma endregion

