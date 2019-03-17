#pragma once

#include <glm/glm.hpp> 

class BasicLight
{
protected :
	glm::vec4 m_Color;
public:
	BasicLight(glm::vec4& color);
	~BasicLight();

	const glm::vec4 GetColor() const;
};