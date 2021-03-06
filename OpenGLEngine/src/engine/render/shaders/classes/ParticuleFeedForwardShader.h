#pragma once

#pragma once

#include <glm/glm.hpp>
#include "../../materials/Material.h"
#include "../../lights/DirectionalLight.h"
#include "../../core/Camera.h"
#include "BasicShader.h"


class ParticuleFeedForwardShader : public ShaderBase
{
private:
	static constexpr auto VERTEX_SHADER{ "./src/engine/render/shaders/src/vertexShaderFeedForward.glsl" };
	const char* OUTPUT_NAMES[3] { "OUT.position", "OUT.startTime", "OUT.velocity" };

protected:
	void ConstructShader() override;
	void CreateUniforms() override;

public:
	ParticuleFeedForwardShader();
	~ParticuleFeedForwardShader();

	void LoadLifeTimeUniform(float value);
	void LoadFrameTimeUniform(float value);
	void LoadSimulationTimeUniform(float value);
	void LoadGravityForceUniform(const glm::vec3& value);
	void LoadAccelerationUniform(const glm::vec3& value);
	void LoadCenterUniform(const glm::vec3& value);

};