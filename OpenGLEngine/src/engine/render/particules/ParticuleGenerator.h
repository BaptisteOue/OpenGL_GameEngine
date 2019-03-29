#pragma once

#include "glm/glm.hpp"
#include <vector>

class ParticuleGenerator
{
private:
	int m_nbParticules;
	std::vector<glm::vec3> m_Positions;
	std::vector<glm::vec3> m_InitialVelocities;
	std::vector<float> m_StartTimes;
public:
	ParticuleGenerator(int nbParticules);
	~ParticuleGenerator();

	const std::vector<glm::vec3>& GetPositions() const;
	const std::vector<glm::vec3>& GetInitialVelocities() const;
	const std::vector<float>& GetStartTimes() const;
	const int GetNbParticules() const;
private:
	void GenerateParticules();
	const glm::vec3& GenerateRandomConeSpeed();
	const float GenerateRandomStartTime();
};