#include "BasicShader.h"
#include "ShaderBase.h"
#include "../core/Camera.h"

const char* BasicShader::VERTEX_SHADER = "./src/engine/render/shaders/vertexShader.glsl";
const char* BasicShader::FRAGMENT_SHADER = "./src/engine/render/shaders/fragmentShader.glsl";

BasicShader::BasicShader()
	: ShaderBase(BasicShader::VERTEX_SHADER, BasicShader::FRAGMENT_SHADER)
{
	
}

BasicShader::~BasicShader()
{
}

void BasicShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
}

void BasicShader::CreateUniforms()
{
	AddUniform("modelMatrix");
	AddUniform("viewMatrix");
	AddUniform("projectionMatrix");

	AddUniform("cameraPos");

	AddUniform("directionalLight.color");
	AddUniform("directionalLight.direction");
	
	AddUniform("material.Ka");
	AddUniform("material.Kd");
	AddUniform("material.Ks");
	AddUniform("material.reflectivity");
	AddUniform("material.shineDamper");
}

void BasicShader::LoadCameraUniform(Camera& camera)
{
	LoadUniform("cameraPos", camera.GetPos());
}

void BasicShader::LoadMatricesUniforms(glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	LoadUniform("modelMatrix", modelMatrix);
	LoadUniform("viewMatrix", viewMatrix);
	LoadUniform("projectionMatrix", projectionMatrix);
}

void BasicShader::LoadMaterialUniforms(Material& material)
{
	LoadUniform("material.Ka", material.GetKa());
	LoadUniform("material.Kd", material.GetKd());
	LoadUniform("material.Ks", material.GetKs());
	LoadUniform("material.reflectivity", material.GetReflectivity());
	LoadUniform("material.shineDamper", material.GetShineDamper());
}

void BasicShader::LoadLightsUniforms(DirectionalLight& directionalLight)
{
	LoadUniform("directionalLight.color", directionalLight.GetColor());
	LoadUniform("directionalLight.direction", directionalLight.GetDirection());
}
