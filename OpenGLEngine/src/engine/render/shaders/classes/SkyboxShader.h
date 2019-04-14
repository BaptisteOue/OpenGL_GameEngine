#pragma once

#include "ShaderBase.h"
#include <glm/glm.hpp>

class SkyboxShader : public ShaderBase
{
private:
	static constexpr auto VERTEX_SHADER{ "./src/engine/render/shaders/src/vertexShaderSkybox.glsl" };
	static constexpr auto FRAGMENT_SHADER{ "./src/engine/render/shaders/src/fragmentShaderSkybox.glsl" };

protected:
	void ConstructShader() override;
	void CreateUniforms() override;

public:
	SkyboxShader();
	~SkyboxShader();

	void LoadMatricesUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
};