#pragma once

#include "BasicShader.h"
#include "glm/common.hpp"

class ShadowMapShader : public BasicShader
{
private:
	static constexpr auto VERTEX_SHADER = "./src/engine/render/shaders/src/vertexShaderUnidirectionalShadowMap.glsl";
	static constexpr auto FRAGMENT_SHADER = "./src/engine/render/shaders/src/fragmentShaderUnidirectionalShadowMap.glsl";

protected:
	void CreateUniforms() override;

public:
	ShadowMapShader();
	~ShadowMapShader();

	void LoadUniforms(glm::mat4 lightSpaceMatrix, glm::mat4 modelMatrix);
};
