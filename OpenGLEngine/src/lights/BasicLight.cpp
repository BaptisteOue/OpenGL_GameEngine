#include "BasicLight.h"



BasicLight::BasicLight(glm::vec3& color)
	: m_Color(color)
{
}


BasicLight::~BasicLight()
{
}

const glm::vec3 BasicLight::GetColor() const
{
	return m_Color;
}
