#pragma once

#include "../../framebuffers/FramBuffer.h"
#include "../../shaders/classes/BasicShader.h"
#include "../../renderers/GameObjectRenderer.h"
#include "../../renderers/ParticuleRender.h"
#include "../../renderers/SkyboxRenderer.h"

class LightingPass
{
private:
	ParticuleRender m_ParticuleRender;
	GameObjectRenderer m_GameObjectRenderer;
	SkyboxRenderer m_SkyboxRenderer;
public:
	LightingPass();
	~LightingPass();

	void Create();
	void ExecuteRenderPass(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems, LightScene & lightScene, 
						   Camera & camera, GLuint shadowMap, float frameTime);
	void CleanUp();

};