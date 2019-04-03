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
	static constexpr float FOV = 45.0f;
	static constexpr float nearPlane = 0.01f;
	static constexpr float farPlane = 1000.0f;

	ParticuleFeedForwardShader m_ParticuleFeedForwardShader;
	ParticuleShader m_ParticuleShader;

public:
	ParticuleRender();
	~ParticuleRender();

	void Init();
	void Render(std::vector<ParticuleSystem> & particuleSystems, LightScene& lightScene, Camera& camera, float frameTime);
	void CleanUp();

};