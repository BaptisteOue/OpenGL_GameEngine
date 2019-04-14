#include "SkyboxShader.h"

SkyboxShader::SkyboxShader()
	: ShaderBase{"SkyboxShader"}
{
	RegisterVertexShader(SkyboxShader::VERTEX_SHADER);
	RegisterFragmentShader(SkyboxShader::FRAGMENT_SHADER);
}

SkyboxShader::~SkyboxShader()
{
}

void SkyboxShader::LoadMatricesUniforms(const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix)
{
	LoadUniform("viewMatrix", viewMatrix);
	LoadUniform("projectionMatrix", projectionMatrix);
}

void SkyboxShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
	LinkProgram(m_Program);
}

void SkyboxShader::CreateUniforms()
{
	AddUniform("viewMatrix");
	AddUniform("projectionMatrix");
}
