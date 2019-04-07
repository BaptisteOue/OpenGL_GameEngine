#pragma once

#include "BasicShader.h"
#include "glm/common.hpp"

class ShadowMapShader : public BasicShader
{
private:
	static constexpr auto VERTEX_SHADER = "./src/engine/render/shaders/src/vertexShaderShadowMap.glsl";
	static constexpr auto FRAGMENT_SHADER = "./src/engine/render/shaders/src/fragmentShaderShadowMap.glsl";
public:
	ShadowMapShader();
	~ShadowMapShader();

	void CreateUniforms() override;
	void LoadUniforms(glm::mat4 lightSpaceMatrix, glm::mat4 modelMatrix);
};
