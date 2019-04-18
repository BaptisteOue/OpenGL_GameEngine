#pragma once

#include "../../framebuffers/FrameBuffer.h"
#include "../../shaders/classes/ShadowMapShader.h"
#include "../../core/Camera.h"

class ShadowmapPass
{
private:
	FrameBuffer m_ShadowMapFB;
	ShadowMapShader m_ShadowMapShader;
public:
	ShadowmapPass();
	~ShadowmapPass();
	void Create();
	void GenerateUnidirectionalShadowMap(std::vector<GameObject>& gameObjects, LightScene& lightScene, Camera& camera);
	void GenerateOmnidirectionalShadowMap();
	GLuint GetUnidirectionalShadowmap();

	void CleanUp();
};