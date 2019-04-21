#pragma once

#include "ShaderBase.h"

class BlurShader : public ShaderBase
{


private:
	static constexpr auto VERTEX_SHADER{ "./src/engine/render/shaders/src/vertexShaderQuad.glsl" };
	static constexpr auto FRAGMENT_SHADER{ "./src/engine/render/shaders/src/fragmentShaderBlur.glsl" };

protected:
	void ConstructShader() override;
	void CreateUniforms() override;

public:
	BlurShader();
	~BlurShader();

	void LoadHorizontalUniform(bool value);
};