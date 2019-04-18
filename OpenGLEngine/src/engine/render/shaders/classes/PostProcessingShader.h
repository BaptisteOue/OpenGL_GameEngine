#pragma once

#include "ShaderBase.h"

class PostProcessingShader : public ShaderBase
{
private:
	static constexpr auto VERTEX_SHADER{ "./src/engine/render/shaders/src/vertexShaderPostProcessing.glsl" };
	static constexpr auto FRAGMENT_SHADER{ "./src/engine/render/shaders/src/fragmentShaderPostProcessing.glsl" };

protected:
	void ConstructShader() override;
	void CreateUniforms() override;

public:
	PostProcessingShader();
	~PostProcessingShader();
};