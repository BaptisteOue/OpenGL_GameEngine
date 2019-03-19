#pragma once

#include <glm/glm.hpp>
#include "ShaderBase.h"
#include "../materials/Material.h"
#include "../lights/DirectionalLight.h"
#include "../lights/PointLight.h"
#include "../lights/SpotLight.h"
#include "../core/Camera.h"


class TesselatedShader : public ShaderBase
{
public:
	static const char* VERTEX_SHADER;
	static const char* TESS_CTRL_SHADER;
	static const char* TESS_EVAL_SHADER;
	static const char* FRAGMENT_SHADER;
private:
	void AddLightUniforms();
	void AddMaterialUniforms();
public:
	TesselatedShader();
	~TesselatedShader();

	void ConstructShader() override;
	void CreateUniforms() override;


	void LoadMatricesUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void LoadTessLevels(float outer, float inner);
	void LoadMaterialUniforms(const Material& material);
	void LoadLightsUniforms(const DirectionalLight& directionalLight, const PointLight& pointLight, const SpotLight& spotLight, const glm::mat4& matrice);
};

