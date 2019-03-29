#include "TesselatedShader.h"


#pragma region Public API

TesselatedShader::TesselatedShader()
	: BasicShader()
{
	RegisterVertexShader(TesselatedShader::VERTEX_SHADER);
	RegisterFragmentShader(TesselatedShader::FRAGMENT_SHADER);
	RegisterTessCtrlShader(TesselatedShader::TESS_CTRL_SHADER);
	RegisterTessEvalShader(TesselatedShader::TESS_EVAL_SHADER);
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
	BasicShader::CreateUniforms();

	AddUniform("tessLevelOuter");
	AddUniform("tessLevelInner");
}

void TesselatedShader::LoadTessLevels(float outer, float inner)
{
	LoadUniform("tessLevelOuter", outer);
	LoadUniform("tessLevelInner", inner);
}

#pragma endregion





