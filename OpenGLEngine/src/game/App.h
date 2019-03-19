#pragma once

#include "../engine/render/core/IGameLogic.h"
#include "../engine/render/core/Camera.h"
#include "../engine/render/shaders/BasicShader.h"
#include "../engine/render/shaders/TesselatedShader.h"
#include "../engine/render/lights/DirectionalLight.h"
#include "../engine/render/lights/PointLight.h"
#include "../engine/render/lights/SpotLight.h"
#include "../engine/render/models/GameObject.h"

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
