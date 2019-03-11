#pragma once

#include <glm/glm.hpp> 

class BasicLight
{
protected :
	glm::vec3 m_Color;
public:
	BasicLight(glm::vec3& color);
	~BasicLight();

	const glm::vec3 GetColor() const;
};