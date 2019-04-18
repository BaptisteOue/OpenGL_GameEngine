#include "LightShader.h"

LightShader::LightShader()
	: ShaderBase{ "LightShader" }
{
	RegisterVertexShader(LightShader::VERTEX_SHADER);
	RegisterFragmentShader(LightShader::FRAGMENT_SHADER);
}

LightShader::~LightShader()
{
}

void LightShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
	LinkProgram(m_Program);
}

void LightShader::CreateUniforms()
{
	AddUniform("lightColor");
	AddUniform("viewMatrix");
	AddUniform("modelMatrix");
	AddUniform("projectionMatrix");
}


void LightShader::LoadMatricesUniforms(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	LoadUniform("modelMatrix", modelMatrix);
	LoadUniform("viewMatrix", viewMatrix);
	LoadUniform("projectionMatrix", projectionMatrix);
}

void LightShader::LoadColorUniform(const glm::vec3& lightColor)
{
	LoadUniform("lightColor", lightColor);
}
