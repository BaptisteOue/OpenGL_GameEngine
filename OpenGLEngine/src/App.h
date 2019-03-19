#pragma once

#include "coreEngine/IGameLogic.h"
#include "coreEngine/Camera.h"
#include "shaders/BasicShader.h"
#include "shaders/TesselatedShader.h"
#include "lights/DirectionalLight.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"
#include "models/GameObject.h"

class App : public IGameLogic
{
private:
	TesselatedShader m_TessShader;
    
	GameObject* m_GameObject;

	DirectionalLight* m_DirecationalLight;
	PointLight* m_PointLight;
	SpotLight* m_SpotLight;

	Camera m_Camera;
	glm::vec3 dCamera;

public:
    App();
    ~App() override;

    void Init() override;
    void Input(Window& window) override;
    void Update(float Interval) override;
    void Render() override;
	void CleanUp() override;
};
