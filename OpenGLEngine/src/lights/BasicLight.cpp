#include "BasicLight.h"



BasicLight::BasicLight(glm::vec4& color)
	: m_Color(color)
{
}


BasicLight::~BasicLight()
{
}

const glm::vec4 BasicLight::GetColor() const
{
	return m_Color;
}
