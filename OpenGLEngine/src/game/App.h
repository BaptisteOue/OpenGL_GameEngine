#pragma once

#include "../engine/render/core/IGameLogic.h"
#include "../engine/render/core/Camera.h"
#include "../engine/render/models/GameObject.h"
#include "../engine/render/lights/LightScene.h"
#include "../engine/render/renderers/MasterRenderer.h"
#include "../engine/render/particules/ParticuleSystem.h"
#include <vector>

class App : public IGameLogic
{
private:
	Camera m_Camera;
	glm::vec3 dCamera;

	LightScene m_LightScene;

	MasterRenderer m_MasterRenderer;

	std::vector<GameObject> m_GameObjects;
	GameObjectRenderer m_GameObjectRenderer;
	
	std::vector<ParticuleSystem> m_ParticuleSystems;
	ParticuleRender m_ParticuleRenderer;

public:
    App();
    ~App() override;

    void Init() override;
    void Input(Window& window) override;
    void Update(float Interval) override;
    void Render(float frameTime) override;
	void CleanUp() override;
};
