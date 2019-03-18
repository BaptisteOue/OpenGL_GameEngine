#pragma once

#include <glm/glm.hpp> 

class BasicLight
{
protected :
	glm::vec3 m_Color;
public:
	BasicLight(const glm::vec3& color);
	~BasicLight();

	const glm::vec3 GetColor() const;
	void SetColor(const glm::vec3& color);
};