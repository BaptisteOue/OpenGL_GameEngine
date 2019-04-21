#include "BloomGammaHDRShader.h"

BloomGammaHDRShader::BloomGammaHDRShader()
	: ShaderBase{"BloomGammaHDRShader"}
{
	RegisterVertexShader(BloomGammaHDRShader::VERTEX_SHADER);
	RegisterFragmentShader(BloomGammaHDRShader::FRAGMENT_SHADER);
}

BloomGammaHDRShader::~BloomGammaHDRShader()
{
}

void BloomGammaHDRShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
	LinkProgram(m_Program);
}

void BloomGammaHDRShader::CreateUniforms()
{
	AddUniform("gamma");
}

void BloomGammaHDRShader::LoadGammaUniform(float gamma)
{
	LoadUniform("gamma", gamma);
}

