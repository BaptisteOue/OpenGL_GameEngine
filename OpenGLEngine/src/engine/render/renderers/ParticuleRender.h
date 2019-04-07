#pragma once

#include "../particules/ParticuleSystem.h"
#include "../shaders/classes/ParticuleShader.h"
#include "../shaders/classes/ParticuleFeedForwardShader.h"
#include "../core/Camera.h"
#include "../lights/LightScene.h"
#include <vector>


class ParticuleRender
{
private:

	ParticuleFeedForwardShader m_ParticuleFeedForwardShader;
	ParticuleShader m_ParticuleShader;

public:
	ParticuleRender();
	~ParticuleRender();

	void Init();
	void Render(std::vector<ParticuleSystem> & particuleSystems, LightScene& lightScene, Camera& camera, GLuint shadowMap, float frameTime);
	void CleanUp();

};