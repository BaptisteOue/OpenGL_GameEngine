#include "LightScene.h"


#pragma region Public API


LightScene::LightScene()
	:m_ambientLight{},
	m_DirecationalLight{},
	m_PointLights{},
	m_SpotLights{}
{
}

LightScene::~LightScene()
{
}

void LightScene::Init()
{
	// Ambient light already done (not a vector)
	m_ambientLight.SetIntensity(0.01f);

	// Directional Lights
	m_DirecationalLight.SetIntensity(1.0f);
	m_DirecationalLight.SetCastShadow(true);
	m_DirecationalLight.SetDirection(glm::vec3(0, -1, -1));

	// Point lights
	PointLight pointLight{ glm::vec3(1, 1, 1), glm::vec3(0, 5, 0), 1.0f };
	pointLight.SetAttenuation(1, 0.1f, 0.02f);
	m_PointLights.push_back(pointLight);

	// Torch
	//pointLight.SetIntensity(2);
	//pointLight.SetColor(glm::vec3(0, 1, 0));
	//pointLight.SetAttenuation(1, 0.1f, 0.02f);
	//m_SpotLights.push_back(SpotLight(pointLight, 10, glm::vec3(0, 0, -1)));

	// Other Spot lights...
	//pointLight.SetAttenuation(1, 0.1f, 0.02f);
	//pointLight.SetIntensity(1);
	//pointLight.SetColor(glm::vec3(1, 1, 0));
	//pointLight.SetPosition(glm::vec3(-30, 30, -30));
	//m_SpotLights.push_back(SpotLight(pointLight, 40, glm::vec3(1, -1, 1)));

	//pointLight.SetColor(glm::vec3(0, 1, 1));
	//pointLight.SetPosition(glm::vec3(30, 30, -30));
	//m_SpotLights.push_back(SpotLight(pointLight, 40, glm::vec3(-1, -1, 1)));

	//pointLight.SetColor(glm::vec3(1, 0, 1));
	//pointLight.SetPosition(glm::vec3(-30, 30, 30));
	//m_SpotLights.push_back(SpotLight(pointLight, 40, glm::vec3(1, -1, -1)));

	//pointLight.SetColor(glm::vec3(1, 1, 1));
	//pointLight.SetPosition(glm::vec3(30, 30, 30));
	//m_SpotLights.push_back(SpotLight(pointLight, 40, glm::vec3(-1, -1, -1)));

}

void LightScene::CleanUp()
{
	m_PointLights.clear();
	m_SpotLights.clear();
}

const BasicLight & LightScene::GetAmbientLight() const
{
	return m_ambientLight;
}

BasicLight & LightScene::GetAmbientLight()
{
	return m_ambientLight;
}

const DirectionalLight& LightScene::GetDirectionalLight() const
{
	return m_DirecationalLight;
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

DirectionalLight& LightScene::GetDirectionalLight()
{
	return m_DirecationalLight;
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