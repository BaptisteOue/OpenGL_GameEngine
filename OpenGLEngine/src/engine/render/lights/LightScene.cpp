#include "LightScene.h"
#include "../utils/Loader.h"


#pragma region Public API


LightScene::LightScene()
	:m_ambientLight{ nullptr },
	m_DirecationalLight{ nullptr },
	m_PointLights{},
	m_SpotLights{}
{

}

LightScene::~LightScene()
{	
}

void LightScene::CleanUp()
{
	m_PointLights.clear();
	m_SpotLights.clear();
}

const BasicLight & LightScene::GetAmbientLight() const
{
	return *m_ambientLight;
}

BasicLight & LightScene::GetAmbientLight()
{
	return *m_ambientLight;
}

const DirectionalLight& LightScene::GetDirectionalLight() const
{
	return *m_DirecationalLight;
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
	return *m_DirecationalLight;
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

void LightScene::SetAmbientLight(const BasicLight& ambientLight)
{
	m_ambientLight = std::make_unique<BasicLight>(ambientLight);
}

void LightScene::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	m_DirecationalLight = std::make_unique<DirectionalLight>(directionalLight);
	Mesh m(Loader::LoadOBJ("./res/sphere.obj"));
	Material material(glm::vec3(directionalLight.GetColor()), glm::vec3(directionalLight.GetColor()), glm::vec3(directionalLight.GetColor()), 0, 1);
	m_LightObjects.emplace_back(m, material, directionalLight.GetFakePosition(), glm::vec3(0), 10.0f);
}

void LightScene::AddPointLight(const PointLight& pointLight)
{
	m_PointLights.emplace_back(pointLight);
	Mesh m(Loader::LoadOBJ("./res/cube.obj"));
	Material material(glm::vec3(pointLight.GetColor()), glm::vec3(pointLight.GetColor()), glm::vec3(pointLight.GetColor()), 0, 1);
	m_LightObjects.emplace_back(m, material, pointLight.GetPosition(), glm::vec3(0), 1.0f);
}

void LightScene::AddSpotLight(const SpotLight& spotLight)
{
	m_SpotLights.emplace_back(spotLight);
	Mesh m(Loader::LoadOBJ("./res/cube.obj"));
	Material material(glm::vec3(spotLight.GetColor()), glm::vec3(spotLight.GetColor()), glm::vec3(spotLight.GetColor()), 0, 1);
	m_LightObjects.emplace_back(m, material, spotLight.GetPosition(), glm::vec3(0), 10.0f);
}

const std::vector<GameObject>& LightScene::GetDebugLightObjects() const
{
	return m_LightObjects;
}

#pragma endregion