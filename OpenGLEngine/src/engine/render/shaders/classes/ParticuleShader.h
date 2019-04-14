#pragma once

#include <glm/glm.hpp>
#include "../../materials/Material.h"
#include "../../lights/DirectionalLight.h"
#include "../../core/Camera.h"
#include "BasicShader.h"


class ParticuleShader : public BasicShader
{
private:
	static constexpr auto VERTEX_SHADER = "./src/engine/render/shaders/src/vertexShaderParticule.glsl";
	static constexpr auto GEOMETRY_SHADER = "./src/engine/render/shaders/src/geometryShaderParticule.glsl";
	static constexpr auto FRAGMENT_SHADER = "./src/engine/render/shaders/src/fragmentShaderParticule.glsl";

protected:
	void ConstructShader() override;
	void CreateUniforms() override;

public:
	ParticuleShader();
	~ParticuleShader();

	void LoadSimulationTimeUniform(float value);
	void LoadLifeTimeUniform(float value);
};