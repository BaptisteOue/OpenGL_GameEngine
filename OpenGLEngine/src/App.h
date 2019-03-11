#pragma once

#include "models/Mesh.h"
#include "coreEngine/IGameLogic.h"
#include "coreEngine/Camera.h"
#include "shaders/BasicShader.h"
#include "materials/Material.h"
#include "lights/DirectionalLight.h"
#include <memory>

class App : public IGameLogic
{
private:
    BasicShader m_BasicShader;
    
	Mesh m_Mesh;
	Material* m_Material;
	DirectionalLight* m_DirecationalLight;

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
