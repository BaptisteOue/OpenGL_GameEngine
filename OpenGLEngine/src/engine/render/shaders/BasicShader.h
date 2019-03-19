#pragma once

#include <glm/glm.hpp>
#include "ShaderBase.h"
#include "../materials/Material.h"
#include "../lights/DirectionalLight.h"
#include "../core/Camera.h"


class BasicShader : public ShaderBase
{
public:
	static const char* VERTEX_SHADER;
	static const char* FRAGMENT_SHADER;
public:
	BasicShader();
	~BasicShader();

	void CreateUniforms() override;
	void ConstructShader() override;
	void LoadCameraUniform(Camera& camera);
	void LoadMatricesUniforms(glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projectionMatrix);
	void LoadMaterialUniforms(Material& material);
	void LoadLightsUniforms(DirectionalLight& directionalLight);
};

