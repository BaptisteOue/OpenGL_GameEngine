#pragma once

#include "../lights/DirectionalLight.h"
#include "../lights/PointLight.h"
#include "../lights/SpotLight.h"
#include "../models/GameObject.h"
#include <vector>
#include <memory>

class LightScene
{
private:
	std::unique_ptr<BasicLight> m_ambientLight;
	std::unique_ptr <DirectionalLight> m_DirecationalLight;
	std::vector<PointLight> m_PointLights;
	std::vector<SpotLight> m_SpotLights;

	std::vector<GameObject> m_LightObjects;

public:
	LightScene();
	~LightScene();

	void CleanUp();

	const BasicLight& GetAmbientLight() const;
	const DirectionalLight& GetDirectionalLight() const;
	const std::vector<PointLight>& GetPointLights() const;
	const std::vector<SpotLight>& GetSpotLights() const;
	const SpotLight& GetTorch() const;

	BasicLight& GetAmbientLight();
	DirectionalLight& GetDirectionalLight();
	std::vector<PointLight>& GetPointLights();
	std::vector<SpotLight>& GetSpotLights();
	SpotLight& GetTorch();


	void SetAmbientLight(const BasicLight& ambientLight);
	void SetDirectionalLight(const DirectionalLight& directionalLight);
	void AddPointLight(const PointLight& pointLight);
	void AddSpotLight(const SpotLight& spotLight);

	// TODO : When lights move gameObjects don't
	const std::vector<GameObject>& GetDebugLightObjects() const;
};