#pragma once

#include "ShaderBase.h"

class HDRGammaShader : public ShaderBase
{
private:
	static constexpr auto VERTEX_SHADER{ "./src/engine/render/shaders/src/vertexShaderPostProcessing.glsl" };
	static constexpr auto FRAGMENT_SHADER{ "./src/engine/render/shaders/src/fragmentShaderPostProcessing.glsl" };

protected:
	void ConstructShader() override;
	void CreateUniforms() override;

public:
	HDRGammaShader();
	~HDRGammaShader();

	void LoadGammaUniform(float gamma = 2.2f);
};