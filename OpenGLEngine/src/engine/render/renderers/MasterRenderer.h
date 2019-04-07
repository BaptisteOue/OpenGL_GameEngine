#pragma once

#include "./GameObjectRenderer.h"
#include "./ParticuleRender.h"
#include "../framebuffers/FramBuffer.h"
#include "../shaders/classes/BasicShader.h"

class MasterRenderer
{
private:
	FrameBuffer m_ShadowMapFB;
	ShadowMapShader m_ShadowMapShader;

	GameObjectRenderer m_GameObjectRender;
	ParticuleRender m_ParticuleRender;
public:
	static constexpr float FOV = 45.0f;
	static constexpr float nearPlane = 0.01f;
	static constexpr float farPlane = 1000.0f;

private:
	void ShadowMapPass(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems, LightScene& lightScene, Camera& camera);
public:
	MasterRenderer();
	~MasterRenderer();

	void Init();
	void Render(std::vector<GameObject>& gameObjects, 
				std::vector<ParticuleSystem> & particuleSystems, 
				LightScene& lightScene, 
				Camera& camera, 
				float frameTime);	
	void CleanUp();
};