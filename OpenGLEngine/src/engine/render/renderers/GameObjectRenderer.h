#pragma once

#include "../models/GameObject.h"
#include "../lights/LightScene.h"
#include "../core/Camera.h"
#include "../shaders/classes/TesselatedShader.h"
#include "../shaders/classes/ShadowMapShader.h"
#include "../framebuffers/FramBuffer.h"

class GameObjectRenderer
{
private:
	static constexpr float FOV = 45.0f;
	static constexpr float nearPlane = 0.01f;
	static constexpr float farPlane = 1000.0f;

	FrameBuffer m_ShadowMapFB;
	ShadowMapShader m_ShadowMapShader;
	BasicShader m_TestShader;
	GLuint m_QuadVAO;

	TesselatedShader m_TesselatedShader;
	

public:
	GameObjectRenderer();
	~GameObjectRenderer();

	void Init();
	void Render(std::vector<GameObject>& gameObject, LightScene& lightScene, Camera& camera);
	void CleanUp();
private:
	void RenderPass(std::vector<GameObject>& gameObjects, LightScene& lightScene, Camera& camera);
	void ShadowMapPass(std::vector<GameObject>& gameObjects, LightScene& lightScene, Camera& camera);

};