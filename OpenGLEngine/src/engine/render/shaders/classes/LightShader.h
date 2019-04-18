#pragma once

#include "ShaderBase.h"

class LightShader : public ShaderBase
{
private:
	static constexpr auto VERTEX_SHADER{ "./src/engine/render/shaders/src/vertexShaderLight.glsl" };
	static constexpr auto FRAGMENT_SHADER{ "./src/engine/render/shaders/src/fragmentShaderLight.glsl" };
protected:
	void ConstructShader() override;
	void CreateUniforms() override;
public:
	LightShader();
	~LightShader();

	void LoadMatricesUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void LoadColorUniform(const glm::vec3& lightColor);
};