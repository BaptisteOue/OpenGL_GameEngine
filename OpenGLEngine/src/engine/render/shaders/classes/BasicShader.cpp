#include "BasicShader.h"
#include "../../core/Camera.h"

#include <iostream>

#pragma region Public API

BasicShader::BasicShader()
	: ShaderBase()
{
	RegisterVertexShader(BasicShader::VERTEX_SHADER);
	RegisterFragmentShader(BasicShader::FRAGMENT_SHADER);
}

BasicShader::BasicShader(const char* vertexShaderPath, const char* fragmentShaderPath)
	: ShaderBase()
{
	RegisterVertexShader(vertexShaderPath);
	RegisterFragmentShader(fragmentShaderPath);
}

BasicShader::~BasicShader()
{
}

void BasicShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
	LinkProgram(m_Program);
}

void BasicShader::CreateUniforms()
{
	AddUniform("modelMatrix");
	AddUniform("viewMatrix");
	AddUniform("projectionMatrix");
	AddUniform("lightSpaceMatrix");

	AddLightUniforms(1, 1, 1);
	AddMaterialUniforms();
}

void BasicShader::LoadMatricesUniforms(const glm::mat4 & modelMatrix,
									   const glm::mat4 & viewMatrix,
									   const glm::mat4 & projectionMatrix,
									   const glm::mat4 & lightSpaceMatrix)
{
	LoadUniform("modelMatrix", modelMatrix);
	LoadUniform("viewMatrix", viewMatrix);
	LoadUniform("projectionMatrix", projectionMatrix);
	LoadUniform("lightSpaceMatrix", lightSpaceMatrix);
}

void BasicShader::LoadMaterialUniforms(const Material& material)
{
	LoadUniform("material.Ka", material.GetKa());
	LoadUniform("material.Kd", material.GetKd());
	LoadUniform("material.Ks", material.GetKs());
	LoadUniform("material.reflectivity", material.GetReflectivity());
	LoadUniform("material.shineDamper", material.GetShineDamper());
	LoadUniform("material.isTextured", material.IsTextured());
}

void BasicShader::LoadLightsUniforms(const LightScene& lightScene, const glm::mat4& matrice)
{
	LoadUniform("numDirectionalLights", (int) lightScene.GetDirectionalLights().size());
	LoadUniform("numPointLights", (int)lightScene.GetPointLights().size());
	LoadUniform("numSpotLights", (int)lightScene.GetSpotLights().size());
	LoadBasicLightUniforms("ambientLight", lightScene.GetAmbientLight());

	auto i = 0;
	for (const DirectionalLight& directionalLight : lightScene.GetDirectionalLights())
	{
		LoadDirectionalLightUniforms("directionalLights[" + std::to_string(i) + "]", directionalLight, matrice);
		i++;
	}

	i = 0;
	for (const PointLight& pointLight : lightScene.GetPointLights())
	{
		LoadPointLightUniforms("pointLights[" + std::to_string(i) + "]", pointLight, matrice);
		i++;
	}

	i = 0;
	for (const SpotLight& spotLight : lightScene.GetSpotLights())
	{
		LoadSpotLightUniforms("spotLights[" + std::to_string(i) + "]", spotLight, matrice);
		i++;
	}
}


#pragma endregion


#pragma region Private API

void BasicShader::AddLightUniforms(int numDir, int numPoint, int numSpot)
{
	AddUniform("numDirectionalLights");
	AddUniform("numPointLights");
	AddUniform("numSpotLights");

	// Add an ambientLight
	AddBasicLightUniforms("ambientLight");

	for (int i = 0; i < numDir; i++)
		AddDirectionalLightUniforms("directionalLights[" + std::to_string(i) + "]");
	for (int i = 0; i < numPoint; i++)
		AddPointLightUniforms("pointLights[" + std::to_string(i) + "]");
	for (int i = 0; i < numSpot; i++)
		AddSpotLightUniforms("spotLights[" + std::to_string(i) + "]");
}

void BasicShader::AddBasicLightUniforms(const std::string & uniformName)
{
	AddUniform(uniformName + ".color");
	AddUniform(uniformName + ".intensity");
}

void BasicShader::AddDirectionalLightUniforms(const std::string & uniformName)
{
	AddBasicLightUniforms(uniformName + ".baseLight");
	AddUniform(uniformName + ".direction");
}

void BasicShader::AddPointLightUniforms(const std::string & uniformName)
{
	AddBasicLightUniforms(uniformName + ".baseLight");
	AddUniform(uniformName + ".position");
	AddUniform(uniformName + ".constAtt");
	AddUniform(uniformName + ".linearAtt");
	AddUniform(uniformName + ".quadraticAtt");
}

void BasicShader::AddSpotLightUniforms(const std::string & uniformName)
{
	AddBasicLightUniforms(uniformName + ".pointLight.baseLight");
	AddPointLightUniforms(uniformName + ".pointLight");
	AddUniform(uniformName + ".cutoffAngle");
	AddUniform(uniformName + ".direction");
}

void BasicShader::AddMaterialUniforms()
{
	AddUniform("material.Ka");
	AddUniform("material.Kd");
	AddUniform("material.Ks");
	AddUniform("material.reflectivity");
	AddUniform("material.shineDamper");
	AddUniform("material.isTextured");
}


void BasicShader::LoadBasicLightUniforms(const std::string& uniformName, const BasicLight & basicLight)
{
	LoadUniform(uniformName + ".color", basicLight.GetColor());
	LoadUniform(uniformName + ".intensity", basicLight.GetIntensity());
}

void BasicShader::LoadDirectionalLightUniforms(const std::string & uniformName, const DirectionalLight & directionalLight, const glm::mat4 & matrice)
{
	LoadBasicLightUniforms(uniformName + ".baseLight", directionalLight);
	LoadUniform(uniformName + ".direction", matrice * glm::vec4(directionalLight.GetDirection(), 0));
}

void BasicShader::LoadPointLightUniforms(const std::string & uniformName, const PointLight & pointLight, const glm::mat4 & matrice)
{
	LoadBasicLightUniforms(uniformName + ".baseLight", pointLight);
	LoadUniform(uniformName + ".constAtt", pointLight.GetConstAtt());
	LoadUniform(uniformName + ".linearAtt", pointLight.GetLinearAtt());
	LoadUniform(uniformName + ".quadraticAtt", pointLight.GetQuadraticAtt());
	LoadUniform(uniformName + ".position", matrice * glm::vec4(pointLight.GetPosition(), 1));
}

void BasicShader::LoadSpotLightUniforms(const std::string & uniformName, const SpotLight & spotLight, const glm::mat4 & matrice)
{
	LoadPointLightUniforms(uniformName + ".pointLight", spotLight, matrice);
	LoadUniform(uniformName + ".cutoffAngle", spotLight.GetCutoffAngle());
	LoadUniform(uniformName + ".direction", matrice * glm::vec4(spotLight.GetDirection(), 0));
}

#pragma endregion


