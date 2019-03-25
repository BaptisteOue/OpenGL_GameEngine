#pragma once

#include <glm/glm.hpp>
#include "ShaderBase.h"
#include "../materials/Material.h"
#include "../lights/BasicLight.h"
#include "../lights/DirectionalLight.h"
#include "../lights/PointLight.h"
#include "../lights/SpotLight.h"
#include "../lights/LightScene.h"
#include "../core/Camera.h"


class TesselatedShader : public ShaderBase
{
public:
	static constexpr auto VERTEX_SHADER = "./src/engine/render/shaders/vertexShader.glsl";
	static constexpr auto TESS_CTRL_SHADER = "./src/engine/render/shaders/tessCtrlShader.glsl";
	static constexpr auto TESS_EVAL_SHADER = "./src/engine/render/shaders/tessEvalShader.glsl";
	static constexpr auto FRAGMENT_SHADER = "./src/engine/render/shaders/fragmentShader.glsl";
private:
	void AddLightUniforms(int numDir, int numPoint, int numSpot);
	void AddBasicLightUniforms(const std::string& uniformName);
	void AddDirectionalLightUniforms(const std::string& uniformName);
	void AddPointLightUniforms(const std::string& uniformName);
	void AddSpotLightUniforms(const std::string& uniformName);

	void AddMaterialUniforms();

	void LoadBasicLightUniforms(const std::string& uniformName, const BasicLight& basicLight);
	void LoadDirectionalLightUniforms(const std::string& uniformName, const DirectionalLight& directionalLight, const glm::mat4& matrice);
	void LoadPointLightUniforms(const std::string& uniformName, const PointLight& pointLight, const glm::mat4& matrice);
	void LoadSpotLightUniforms(const std::string& uniformName, const SpotLight& spotLight, const glm::mat4& matrice);
public:
	TesselatedShader();
	~TesselatedShader();

	void ConstructShader() override;
	void CreateUniforms() override;


	void LoadMatricesUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void LoadTessLevels(float outer, float inner);
	void LoadMaterialUniforms(const Material& material);
	void LoadLightsUniforms(const LightScene& lightScene, const glm::mat4& matrice);
};

