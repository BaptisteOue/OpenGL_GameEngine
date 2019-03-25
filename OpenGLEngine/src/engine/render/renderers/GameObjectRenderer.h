#pragma once

#include "../models/GameObject.h"
#include "../lights/LightScene.h"
#include "../core/Camera.h"
#include "../shaders/TesselatedShader.h"

class GameObjectRenderer
{
private:
	static constexpr float FOV = 45.0f;
	static constexpr float nearPlane = 0.01f;
	static constexpr float farPlane = 1000.0f;

	TesselatedShader m_TesselatedShader;

public:
	GameObjectRenderer();
	~GameObjectRenderer();

	void Init();
	void Render(std::vector<GameObject>& gameObject, LightScene& lightScene, Camera& camera);
	void CleanUp();

};