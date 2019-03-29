#pragma once

#include "../particules/ParticuleSystem.h"
#include "../shaders/ParticuleShader.h"
#include "../core/Camera.h"


class ParticuleRender
{
private:
	static constexpr float FOV = 45.0f;
	static constexpr float nearPlane = 0.01f;
	static constexpr float farPlane = 1000.0f;

	ParticuleShader m_ParticuleShader;

public:
	ParticuleRender();
	~ParticuleRender();

	void Init();
	void Render(ParticuleSystem& particuleSystem, Camera& camera);
	void CleanUp();

};