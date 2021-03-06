#pragma once

#include "../models/GameObject.h"
#include "../lights/LightScene.h"
#include "../core/Camera.h"
#include "../shaders/classes/TesselatedShader.h"
#include "../shaders/classes/ShadowMapShader.h"
#include "../framebuffers/FrameBuffer.h"
#include "renderpass/RenderPassOutput.h"

class GameObjectRenderer
{
	BasicShader m_GameObjectShader;

public:
	GameObjectRenderer();
	~GameObjectRenderer();

	void Init();
	void Render(std::vector<GameObject>& gameObject, LightScene& lightScene, Camera& camera, ShadowmapPassOutput& shadowMapOutput);
	void CleanUp();

};