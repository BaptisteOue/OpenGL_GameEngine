#include "PostProcessingShader.h"

PostProcessingShader::PostProcessingShader()
	: ShaderBase{"PostprocessingShader"}
{
	RegisterVertexShader(PostProcessingShader::VERTEX_SHADER);
	RegisterFragmentShader(PostProcessingShader::FRAGMENT_SHADER);
}

PostProcessingShader::~PostProcessingShader()
{
}

void PostProcessingShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
	LinkProgram(m_Program);
}

void PostProcessingShader::CreateUniforms()
{
}

