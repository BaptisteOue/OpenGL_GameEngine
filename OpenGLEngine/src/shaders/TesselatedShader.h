#pragma once

#include <glm/glm.hpp>
#include "ShaderBase.h"
#include "../materials/Material.h"
#include "../lights/DirectionalLight.h"
#include "../coreEngine/Camera.h"


class TesselatedShader : public ShaderBase
{
public:
	static const char* VERTEX_SHADER;
	static const char* TESS_CTRL_SHADER;
	static const char* TESS_EVAL_SHADER;
	static const char* FRAGMENT_SHADER;
public:
	TesselatedShader();
	~TesselatedShader();

	void ConstructShader() override;
	void CreateUniforms() override;

	void LoadMatricesUniforms(glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projectionMatrix);
	void LoadTessLevels(float outer, float inner);
	void LoadMaterialUniforms(Material& material);
	void LoadLightsUniforms(DirectionalLight& directionalLight, glm::mat4& matrice);
};

