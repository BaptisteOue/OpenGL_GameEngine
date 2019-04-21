#pragma once

#include "./ParticuleRender.h"
#include "./renderpass/ShadowmapPass.h"
#include "./renderpass/LightingPass.h"
#include "./renderpass/BloomGammaHDRPass.h"
#include "./renderpass/BlurPass.h"

class MasterRenderer
{
private:

	// Render passes
	ShadowmapPass m_ShadowmapPass;
	LightingPass m_LightingPass;
	BlurPass m_BlurPass;
	BloomGammaHDRPass m_GammaBloomHDRPass;

	GLuint m_PolygonMode;

public:
	static constexpr float FOV = 45.0f;
	static constexpr float nearPlane = 0.01f;
	static constexpr float farPlane = 1000.0f;

public:
	MasterRenderer();
	~MasterRenderer();

	void Init();
	void SetPolygonMode(GLuint polygonMode);
	void Render(std::vector<GameObject>& gameObjects, 
				std::vector<ParticuleSystem> & particuleSystems, 
				LightScene& lightScene, 
				Camera& camera, 
				float frameTime);	
	void CleanUp();
};