#pragma once

#include "../lights/DirectionalLight.h"
#include "../lights/PointLight.h"
#include "../lights/SpotLight.h"
#include <vector>

class LightScene
{
private:
	BasicLight m_ambientLight;
	std::vector<DirectionalLight> m_DirecationalLights;
	std::vector<PointLight> m_PointLights;
	std::vector<SpotLight> m_SpotLights;

public:
	LightScene();
	~LightScene();

	void Init();
	void CleanUp();

	const BasicLight& GetAmbientLight() const;
	const std::vector<DirectionalLight>& GetDirectionalLights() const;
	const std::vector<PointLight>& GetPointLights() const;
	const std::vector<SpotLight>& GetSpotLights() const;
	const SpotLight& GetTorch() const;

	BasicLight& GetAmbientLight();
	std::vector<DirectionalLight>& GetDirectionalLights();
	std::vector<PointLight>& GetPointLights();
	std::vector<SpotLight>& GetSpotLights();
	SpotLight& GetTorch();
};