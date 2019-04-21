#include "BlurShader.h"

BlurShader::BlurShader()
	: ShaderBase{"BloomShader"}
{
	RegisterVertexShader(BlurShader::VERTEX_SHADER);
	RegisterFragmentShader(BlurShader::FRAGMENT_SHADER);
}

BlurShader::~BlurShader()
{
}

void BlurShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
	LinkProgram(m_Program);
}

void BlurShader::CreateUniforms()
{
	AddUniform("horizontal");
}

void BlurShader::LoadHorizontalUniform(bool value)
{
	LoadUniform("horizontal", value);
}

