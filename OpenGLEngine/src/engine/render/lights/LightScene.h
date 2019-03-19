#pragma once

#include "../lights/DirectionalLight.h"
#include "../lights/PointLight.h"
#include "../lights/SpotLight.h"

class LightScene
{
private:
	DirectionalLight* m_DirecationalLight;
	PointLight* m_PointLight;
	SpotLight* m_SpotLight;
public:
	LightScene();
	~LightScene();

	void Init();
	void CleanUp();

	DirectionalLight& GetDirectionalLight() const;
	PointLight& GetPointLight() const;
	SpotLight& GetSpotLight() const;
};