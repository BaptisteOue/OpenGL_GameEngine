#include "TesselatedShader.h"
#include "ShaderBase.h"
#include "../coreEngine/Camera.h"

const char* TesselatedShader::VERTEX_SHADER = "./src/shaders/vertexShader.glsl";
const char* TesselatedShader::TESS_CTRL_SHADER = "./src/shaders/tessCtrlShader.glsl";
const char* TesselatedShader::TESS_EVAL_SHADER = "./src/shaders/tessEvalShader.glsl";
const char* TesselatedShader::FRAGMENT_SHADER = "./src/shaders/fragmentShader.glsl";

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

	AddUniform("directionalLight.color");
	AddUniform("directionalLight.direction");

	AddUniform("material.Ka");
	AddUniform("material.Kd");
	AddUniform("material.Ks");
	AddUniform("material.reflectivity");
	AddUniform("material.shineDamper");
}

void TesselatedShader::LoadMatricesUniforms(glm::mat4 & modelMatrix, glm::mat4 & viewMatrix, glm::mat4 & projectionMatrix)
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

void TesselatedShader::LoadMaterialUniforms(Material& material)
{
	LoadUniform("material.Ka", material.GetKa());
	LoadUniform("material.Kd", material.GetKd());
	LoadUniform("material.Ks", material.GetKs());
	LoadUniform("material.reflectivity", material.GetReflectivity());
	LoadUniform("material.shineDamper", material.GetShineDamper());
}

void TesselatedShader::LoadLightsUniforms(DirectionalLight& directionalLight, glm::mat4& matrices)
{
	LoadUniform("directionalLight.color", directionalLight.GetColor());
	LoadUniform("directionalLight.direction", matrices * directionalLight.GetDirection());
}
