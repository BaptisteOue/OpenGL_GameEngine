#pragma once

#include <glm/glm.hpp>
#include "../materials/Material.h"
#include "../lights/DirectionalLight.h"
#include "../core/Camera.h"
#include "BasicShader.h"


class ParticuleShader : public BasicShader
{
public:
	static constexpr auto VERTEX_SHADER = "./src/engine/render/shaders/src/vertexShaderParticule.glsl";
	static constexpr auto FRAGMENT_SHADER = "./src/engine/render/shaders/src/fragmentShaderParticule.glsl";
public:
	ParticuleShader();
	~ParticuleShader();

	void CreateUniforms() override;

	void LoadLifeTimeUniform(float value);
	void LoadSimulationTimeUniform(float value);
	void LoadGravityForceUniform(const glm::vec3& value);
};