#pragma once

#include "../../framebuffers/FramBuffer.h"
#include "../../shaders/classes/ShadowMapShader.h"

class ShadowmapPass
{
private:
	FrameBuffer m_ShadowMapFB;
	ShadowMapShader m_ShadowMapShader;
public:
	ShadowmapPass();
	~ShadowmapPass();
	void Create();
	void GenerateShadowMap(std::vector<GameObject>& gameObjects, LightScene& lightScene);
	GLuint GetShadowmap();

	void CleanUp();
};