#pragma once

#include "../../framebuffers/FrameBuffer.h"
#include "../../shaders/classes/BasicShader.h"
#include "../../renderers/GameObjectRenderer.h"
#include "../../renderers/ParticuleRender.h"
#include "../../renderers/SkyboxRenderer.h"
#include "../../renderers/LightRenderer.h"


class LightingPass
{
private:
	ParticuleRender m_ParticuleRender;
	GameObjectRenderer m_GameObjectRenderer;
	SkyboxRenderer m_SkyboxRenderer;
	LightRenderer m_LightRenderer;
public:
	LightingPass();
	~LightingPass();

	void Create();
	void ExecuteRenderPass(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems, LightScene & lightScene, 
						   Camera & camera, GLuint shadowMap, float frameTime);
	void CleanUp();

};