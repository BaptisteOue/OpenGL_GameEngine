#pragma once

#include "ShaderBase.h"

class BloomGammaHDRShader : public ShaderBase
{
private:
	static constexpr auto VERTEX_SHADER{ "./src/engine/render/shaders/src/vertexShaderQuad.glsl" };
	static constexpr auto FRAGMENT_SHADER{ "./src/engine/render/shaders/src/fragmentShaderBloomGammaHDR.glsl" };

protected:
	void ConstructShader() override;
	void CreateUniforms() override;

public:
	BloomGammaHDRShader();
	~BloomGammaHDRShader();

	void LoadGammaUniform(float gamma = 2.2f);
};