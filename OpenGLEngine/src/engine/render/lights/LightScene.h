#pragma once

#include "../lights/DirectionalLight.h"
#include "../lights/PointLight.h"
#include "../lights/SpotLight.h"
#include <vector>

class LightScene
{
private:
	BasicLight m_ambientLight;
	DirectionalLight m_DirecationalLight;
	std::vector<PointLight> m_PointLights;
	std::vector<SpotLight> m_SpotLights;

public:
	LightScene();
	~LightScene();

	void Init();
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
};