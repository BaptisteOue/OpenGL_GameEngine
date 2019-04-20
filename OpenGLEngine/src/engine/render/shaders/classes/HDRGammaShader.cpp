#include "HDRGammaShader.h"

HDRGammaShader::HDRGammaShader()
	: ShaderBase{"HDRGammaShader"}
{
	RegisterVertexShader(HDRGammaShader::VERTEX_SHADER);
	RegisterFragmentShader(HDRGammaShader::FRAGMENT_SHADER);
}

HDRGammaShader::~HDRGammaShader()
{
}

void HDRGammaShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
	LinkProgram(m_Program);
}

void HDRGammaShader::CreateUniforms()
{
	AddUniform("gamma");
}

void HDRGammaShader::LoadGammaUniform(float gamma)
{
	LoadUniform("gamma", gamma);
}

