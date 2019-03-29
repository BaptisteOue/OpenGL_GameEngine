#pragma once

#include "ParticuleGenerator.h"
#include "ParticuleGroup.h"
#include <chrono>

class ParticuleSystem
{
private:
	glm::vec3 m_Center;
	glm::vec3 m_GravityForce;
	std::chrono::steady_clock::time_point m_StartedTime;
	float m_ParticuleLifetime;
	int m_NbParticules;

	ParticuleGenerator m_ParticuleGenerator;
	ParticuleGroup m_ParticuleGroup;

public:
	ParticuleSystem(int nbParticule = 1000, glm::vec3 center = glm::vec3{ 0 }, glm::vec3 gravityForce = glm::vec3{ 0 }, float lifeTime = 3.0f);
	~ParticuleSystem();
	void Init();

	const glm::vec3& GetCenter() const;
	const glm::vec3& GetGravityForce() const;
	float GetSimulationTime() const;
	float GetParticuleLifetime() const;
	const ParticuleGroup& GetParticuleGroup() const;

	void SetCenter(const glm::vec3 value);
	void SetGravityForce(const glm::vec3 value);
	void SetParticuleLifeTime(const float value);
};