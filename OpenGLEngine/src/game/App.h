#pragma once

#include "../engine/render/core/IGameLogic.h"
#include "../engine/render/core/Camera.h"
#include "../engine/render/models/GameObject.h"
#include "../engine/render/lights/LightScene.h"
#include "../engine/render/renderers/GameObjectRenderer.h"
#include <vector>

class App : public IGameLogic
{
private:
	Camera m_Camera;
	glm::vec3 dCamera;

	GameObjectRenderer m_GameObjectRenderer;
	std::vector<GameObject> m_GameObjects;
	LightScene m_LightScene;

public:
    App();
    ~App() override;

    void Init() override;
    void Input(Window& window) override;
    void Update(float Interval) override;
    void Render() override;
	void CleanUp() override;
};
