#include "TesselatedShader.h"

const char* TesselatedShader::VERTEX_SHADER = "./src/engine/render/shaders/vertexShader.glsl";
const char* TesselatedShader::TESS_CTRL_SHADER = "./src/engine/render/shaders/tessCtrlShader.glsl";
const char* TesselatedShader::TESS_EVAL_SHADER = "./src/engine/render/shaders/tessEvalShader.glsl";
const char* TesselatedShader::FRAGMENT_SHADER = "./src/engine/render/shaders/fragmentShader.glsl";

#pragma region Public API

TesselatedShader::TesselatedShader()
	: ShaderBase(TesselatedShader::VERTEX_SHADER, TesselatedShader::FRAGMENT_SHADER,
		TesselatedShader::TESS_CTRL_SHADER, TesselatedShader::TESS_EVAL_SHADER)
{
}

TesselatedShader::~TesselatedShader()
{
}

void TesselatedShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_TessCtrlShader = CreateTessCtrlShader();
	m_TessEvalShader = CreateTessEvalShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
}

void TesselatedShader::CreateUniforms()
{
	AddUniform("modelMatrix");
	AddUniform("viewMatrix");
	AddUniform("projectionMatrix");

	AddUniform("tessLevelOuter");
	AddUniform("tessLevelInner");

	AddLightUniforms();
	AddMaterialUniforms();	
}

void TesselatedShader::LoadMatricesUniforms(const glm::mat4 & modelMatrix, const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix)
{
	LoadUniform("modelMatrix", modelMatrix);
	LoadUniform("viewMatrix", viewMatrix);
	LoadUniform("projectionMatrix", projectionMatrix);
}

void TesselatedShader::LoadTessLevels(float outer, float inner)
{
	LoadUniform("tessLevelOuter", outer);
	LoadUniform("tessLevelInner", inner);
}

void TesselatedShader::LoadMaterialUniforms(const Material& material)
{
	LoadUniform("material.Ka", material.GetKa());
	LoadUniform("material.Kd", material.GetKd());
	LoadUniform("material.Ks", material.GetKs());
	LoadUniform("material.reflectivity", material.GetReflectivity());
	LoadUniform("material.shineDamper", material.GetShineDamper());
	LoadUniform("material.isTextured", material.IsTextured());
}

void TesselatedShader::LoadLightsUniforms(const DirectionalLight& directionalLight, const PointLight& pointLight, const SpotLight& spotLight, const glm::mat4& matrice)
{

	LoadDirectionalLightUniforms("directionalLight", directionalLight, matrice);

	LoadPointLightUniforms("pointLight", pointLight, matrice);

	LoadSpotLightUniforms("spotLight", spotLight, matrice);
}

#pragma endregion


#pragma region Private API

void TesselatedShader::AddLightUniforms()
{
	AddDirectionalLightUniforms("directionalLight");
	AddPointLightUniforms("pointLight");
	AddSpotLightUniforms("spotLight");	
}

void TesselatedShader::AddBasicLightUniforms(const std::string & uniformName)
{
	AddUniform(uniformName + ".color");
	AddUniform(uniformName + ".intensity");
}

void TesselatedShader::AddDirectionalLightUniforms(const std::string & uniformName)
{
	AddBasicLightUniforms(uniformName + ".baseLight");
	AddUniform(uniformName + ".direction");
}

void TesselatedShader::AddPointLightUniforms(const std::string & uniformName)
{
	AddBasicLightUniforms(uniformName + ".baseLight");
	AddUniform(uniformName + ".position");
	AddUniform(uniformName + ".constAtt");
	AddUniform(uniformName + ".linearAtt");
	AddUniform(uniformName + ".quadraticAtt");
}

void TesselatedShader::AddSpotLightUniforms(const std::string & uniformName)
{
	AddBasicLightUniforms(uniformName + ".pointLight.baseLight");
	AddPointLightUniforms(uniformName + ".pointLight");
	AddUniform(uniformName + ".cutoffAngle");
	AddUniform(uniformName + ".direction");
}

void TesselatedShader::AddMaterialUniforms()
{
	AddUniform("material.Ka");
	AddUniform("material.Kd");
	AddUniform("material.Ks");
	AddUniform("material.reflectivity");
	AddUniform("material.shineDamper");
	AddUniform("material.isTextured");
}


void TesselatedShader::LoadBasicLightUniforms(const std::string& uniformName, const BasicLight & basicLight)
{
	LoadUniform(uniformName + ".color", basicLight.GetColor());
	LoadUniform(uniformName + ".intensity", basicLight.GetIntensity());
}

void TesselatedShader::LoadDirectionalLightUniforms(const std::string & uniformName, const DirectionalLight & directionalLight, const glm::mat4 & matrice)
{
	LoadBasicLightUniforms(uniformName + ".baseLight", directionalLight);
	LoadUniform(uniformName + ".direction", matrice * glm::vec4(directionalLight.GetDirection(), 0));
}

void TesselatedShader::LoadPointLightUniforms(const std::string & uniformName, const PointLight & pointLight, const glm::mat4 & matrice)
{
	LoadBasicLightUniforms(uniformName + ".baseLight", pointLight);
	LoadUniform(uniformName + ".constAtt", pointLight.GetConstAtt());
	LoadUniform(uniformName + ".linearAtt", pointLight.GetLinearAtt());
	LoadUniform(uniformName + ".quadraticAtt", pointLight.GetQuadraticAtt());
	LoadUniform(uniformName + ".position", matrice * glm::vec4(pointLight.GetPosition(), 1));
}

void TesselatedShader::LoadSpotLightUniforms(const std::string & uniformName, const SpotLight & spotLight, const glm::mat4 & matrice)
{
	LoadPointLightUniforms(uniformName + ".pointLight", spotLight, matrice);
	LoadUniform(uniformName + ".cutoffAngle", spotLight.GetCutoffAngle());
	LoadUniform(uniformName + ".direction", matrice * glm::vec4(spotLight.GetDirection(), 0));
}

#pragma endregion






