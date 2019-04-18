#pragma once

#include "../core/Camera.h"
#include "../models/GameObject.h"
#include "../shaders/classes/LightShader.h"
#include "../lights/LightScene.h"
#include <vector>

class LightRenderer
{
private:
	LightShader m_LightShader;

public:
	LightRenderer();
	~LightRenderer();

	void Init();
	void Render(const LightScene& lightScene, Camera& camera);
	void CleanUp();

};