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
}

void TesselatedShader::LoadLightsUniforms(const DirectionalLight& directionalLight, const PointLight& pointLight, const SpotLight& spotLight, const glm::mat4& matrice)
{
	LoadUniform("directionalLight.color", directionalLight.GetColor());
	LoadUniform("directionalLight.direction", matrice * glm::vec4(directionalLight.GetDirection(), 0));

	LoadUniform("pointLight.color", pointLight.GetColor());
	LoadUniform("pointLight.constAtt", pointLight.GetConstAtt());
	LoadUniform("pointLight.linearAtt", pointLight.GetLinearAtt());
	LoadUniform("pointLight.quadraticAtt", pointLight.GetQuadraticAtt());
	LoadUniform("pointLight.position", matrice * glm::vec4(pointLight.GetPosition(), 1));

	LoadUniform("spotLight.pointLight.color", spotLight.GetColor());
	LoadUniform("spotLight.pointLight.constAtt", spotLight.GetConstAtt());
	LoadUniform("spotLight.pointLight.linearAtt", spotLight.GetLinearAtt());
	LoadUniform("spotLight.pointLight.quadraticAtt", spotLight.GetQuadraticAtt());
	LoadUniform("spotLight.pointLight.position", matrice * glm::vec4(spotLight.GetPosition(), 1));
	LoadUniform("spotLight.cutoffAngle", spotLight.GetCutoffAngle());
	LoadUniform("spotLight.direction", matrice * glm::vec4(spotLight.GetDirection(), 0));
}

#pragma endregion


#pragma region Private API

void TesselatedShader::AddLightUniforms()
{
	AddUniform("directionalLight.color");
	AddUniform("directionalLight.direction");

	AddUniform("pointLight.color");
	AddUniform("pointLight.position");
	AddUniform("pointLight.constAtt");
	AddUniform("pointLight.linearAtt");
	AddUniform("pointLight.quadraticAtt");

	AddUniform("spotLight.pointLight.color");
	AddUniform("spotLight.pointLight.constAtt");
	AddUniform("spotLight.pointLight.linearAtt");
	AddUniform("spotLight.pointLight.quadraticAtt");
	AddUniform("spotLight.pointLight.position");
	AddUniform("spotLight.cutoffAngle");
	AddUniform("spotLight.direction");
}

void TesselatedShader::AddMaterialUniforms()
{
	AddUniform("material.Ka");
	AddUniform("material.Kd");
	AddUniform("material.Ks");
	AddUniform("material.reflectivity");
	AddUniform("material.shineDamper");
}
#pragma endregion






