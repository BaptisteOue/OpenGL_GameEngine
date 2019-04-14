#pragma once

#include "glm/glm.hpp"
#include <vector>

class ParticuleGenerator
{
public:
	static constexpr float MIN_SPEED = 10.0f;
	static constexpr float MAX_SPEED = 17.0f;
	static constexpr float MIN_ANGLE = 10.0f;
	static constexpr float MAX_ANGLE = 25.0f;
	static constexpr float MIN_START_TIME = 1.0f;
	static constexpr float MAX_START_TIME = 22.0f;
private:
	int m_NbParticules;
	std::vector<glm::vec3> m_Positions;
	std::vector<glm::vec3> m_InitialVelocities;
	std::vector<float> m_StartTimes;
public:
	ParticuleGenerator(int nbParticules);
	~ParticuleGenerator();

	void Init();

	const std::vector<glm::vec3>& GetPositions() const;
	const std::vector<glm::vec3>& GetInitialVelocities() const;
	const std::vector<float>& GetStartTimes() const;
	const int GetNbParticules() const;
	void SetNbParticules(int value);
private:
	void GenerateParticules();
	glm::vec3 GenerateRandomConeSpeed();
	const float GenerateRandomStartTime();
};