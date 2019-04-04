#pragma once

#include "ParticuleGenerator.h"
#include "ParticuleGroup.h"
#include "../materials/Material.h"
#include <chrono>

class ParticuleSystem
{
private:
	glm::vec3 m_Center;
	glm::vec3 m_GravityForce;
	glm::vec3 m_Acceleration;
	std::chrono::steady_clock::time_point m_StartedTime;
	float m_ParticuleLifetime;
	int m_NbParticules;
	ParticuleGenerator m_ParticuleGenerator;
	ParticuleGroup m_ParticuleGroup;
	Material m_Material;

public:
	ParticuleSystem(int nbParticule = 100000, 
		glm::vec3 center = glm::vec3{ 0 }, 
		glm::vec3 gravityForce = glm::vec3{ 0, -1.0f, 0.0f }, 
		glm::vec3 acceleration = glm::vec3{ 0 },
		float lifeTime = 1.0f,
		const Material& material = Material{});
	~ParticuleSystem();
	void Init();

	const glm::vec3& GetCenter() const;
	const glm::vec3& GetGravityForce() const;
	const glm::vec3& GetAcceleration() const;
	float GetSimulationTime() const;
	float GetParticuleLifetime() const;
	const Material& GetMaterial() const;
	Material& GetMaterial();
	ParticuleGroup& GetParticuleGroup();

	void SetCenter(const glm::vec3& value);
	void SetGravityForce(const glm::vec3& value);
	void SetAcceleration(const glm::vec3& value);
	void SetParticuleLifeTime(const float value);
	void SetMaterial(const Material& value);
};