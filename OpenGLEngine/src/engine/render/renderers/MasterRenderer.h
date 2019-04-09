#pragma once

#include "./ParticuleRender.h"
#include "./renderpass/ShadowmapPass.h"
#include "./renderpass/LightingPass.h"

class MasterRenderer
{
private:

	// Render passes
	ShadowmapPass m_ShadowmapPass;
	LightingPass m_LightingPass;

public:
	static constexpr float FOV = 45.0f;
	static constexpr float nearPlane = 0.01f;
	static constexpr float farPlane = 1000.0f;

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