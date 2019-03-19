#include "LightScene.h"

LightScene::LightScene()
	:m_DirecationalLight(nullptr),
	m_PointLight(nullptr),
	m_SpotLight(nullptr)
{
}

LightScene::~LightScene()
{
}

void LightScene::Init()
{
	// Directional Light
	m_DirecationalLight = new DirectionalLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(-1, -1, -1));

	// Spot light
	m_PointLight = new PointLight(glm::vec3(0, 0.4f, 0.7f), glm::vec3(0, 1.5f, 3), 2);
	m_PointLight->SetAttenuation(1, 0.2f, 0.02f);
	m_SpotLight = new SpotLight(*m_PointLight, 10, glm::vec3(0, 0, -1));

	// Point light
	m_PointLight->SetIntensity(10);
	m_PointLight->SetPosition(glm::vec3(2, 2, 0));
	m_PointLight->SetColor(glm::vec3(1, 0, 0));
}

void LightScene::CleanUp()
{
	delete m_DirecationalLight;
	delete m_PointLight;
	delete m_SpotLight;
}

DirectionalLight& LightScene::GetDirectionalLight() const
{
	return *m_DirecationalLight;
}

PointLight& LightScene::GetPointLight() const
{
	return *m_PointLight;
}

SpotLight& LightScene::GetSpotLight() const
{
	return *m_SpotLight;
}
