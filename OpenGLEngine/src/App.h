#pragma once

#include "models/Mesh.h"
#include "coreEngine/IGameLogic.h"
#include "shaders/ShaderProgram.h"
#include "coreEngine/Camera.h"

class App : public IGameLogic
{
private:
    ShaderProgram m_ShaderProgram;
    Mesh m_Mesh;
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
