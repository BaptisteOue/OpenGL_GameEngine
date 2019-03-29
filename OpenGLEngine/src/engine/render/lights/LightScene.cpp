#include "LightScene.h"


#pragma region Public API


LightScene::LightScene()
	:m_DirecationalLights(),
	m_PointLights(),
	m_SpotLights()
{
}

LightScene::~LightScene()
{
}

void LightScene::Init()
{
	// Directional Lights
	m_DirecationalLights.push_back(DirectionalLight(glm::vec3(1), glm::vec3(1, -1, 1), 0.6f));

	// Point lights
	PointLight pointLight(glm::vec3(1, 0, 0), glm::vec3(-10, 20, 0), 4);
	pointLight.SetAttenuation(1, 0.2f, 0.02f);
	m_PointLights.push_back(pointLight);

	pointLight.SetColor(glm::vec3(0, 1, 0));
	pointLight.SetPosition(glm::vec3(0, 20, 0));
	m_PointLights.push_back(pointLight);

	pointLight.SetColor(glm::vec3(0, 0, 1));
	pointLight.SetPosition(glm::vec3(10, 20, 0));
	m_PointLights.push_back(pointLight);

	// Torch
	pointLight.SetIntensity(4);
	pointLight.SetColor(glm::vec3(1));
	m_SpotLights.push_back(SpotLight(pointLight, 10, glm::vec3(0, 0, -1)));

	// Other Spot lights...
	pointLight.SetColor(glm::vec3(1, 1, 0));
	pointLight.SetPosition(glm::vec3(0, 20, -60));
	m_SpotLights.push_back(SpotLight(pointLight, 60, glm::vec3(0, -1, 1)));

	pointLight.SetColor(glm::vec3(0, 1, 1));
	pointLight.SetPosition(glm::vec3(0, 20, 60));
	m_SpotLights.push_back(SpotLight(pointLight, 60, glm::vec3(0, -1, -1)));

	pointLight.SetColor(glm::vec3(1, 0, 1));
	pointLight.SetPosition(glm::vec3(-60, 20, 0));
	m_SpotLights.push_back(SpotLight(pointLight, 60, glm::vec3(1, -1, 0)));

	pointLight.SetColor(glm::vec3(1, 1, 1));
	pointLight.SetPosition(glm::vec3(60, 20, 0));
	m_SpotLights.push_back(SpotLight(pointLight, 60, glm::vec3(-1, -1, 0)));

}

void LightScene::CleanUp()
{
	m_DirecationalLights.clear();
	m_PointLights.clear();
	m_SpotLights.clear();
}

const std::vector<DirectionalLight>& LightScene::GetDirectionalLights() const
{
	return m_DirecationalLights;
}

const std::vector<PointLight>& LightScene::GetPointLights() const
{
	return m_PointLights;
}

const std::vector<SpotLight>& LightScene::GetSpotLights() const
{
	return m_SpotLights;
}

const SpotLight & LightScene::GetTorch() const
{
	return m_SpotLights[0];
}

std::vector<DirectionalLight>& LightScene::GetDirectionalLights()
{
	return m_DirecationalLights;
}

std::vector<PointLight>& LightScene::GetPointLights()
{
	return m_PointLights;
}

std::vector<SpotLight>& LightScene::GetSpotLights()
{
	return m_SpotLights;
}

SpotLight & LightScene::GetTorch()
{
	return m_SpotLights[0];
}

#pragma endregion