#pragma once

#include "../models/GameObject.h"
#include "../lights/LightScene.h"
#include "../core/Camera.h"
#include "../shaders/TesselatedShader.h"

class GameObjectRenderer
{
private:
	const float FOV = 45.0f;
	const float nearPlane = 0.01f;
	const float farPlane = 1000.0f;

	TesselatedShader m_TesselatedShader;

public:
	GameObjectRenderer();
	~GameObjectRenderer();

	void Init();
	void Render(std::vector<GameObject>& gameObject, LightScene& lightScene, Camera& camera);
	void CleanUp();

};