#include "ParticuleShader.h"
#include <iostream>

#pragma region Public API

ParticuleShader::ParticuleShader()
	: BasicShader()
{
	// Override BasicShader shaders paths
	RegisterVertexShader(ParticuleShader::VERTEX_SHADER);
	RegisterGeometryShader(ParticuleShader::GEOMETRY_SHADER);
	RegisterFragmentShader(ParticuleShader::FRAGMENT_SHADER);
}

ParticuleShader::~ParticuleShader()
{
}

void ParticuleShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_GeometryShader = CreateGeometryShader();
	m_FragmentShader = CreateFragmentShader();
	m_Program = CreateProgram();
	LinkProgram(m_Program);
}

void ParticuleShader::CreateUniforms()
{
	AddLightUniforms(1, 10, 5);

	AddUniform("modelMatrix");
	AddUniform("viewMatrix");
	AddUniform("projectionMatrix");
	AddUniform("lifeTime");
	AddUniform("time");

}

void ParticuleShader::LoadSimulationTimeUniform(float value)
{
	LoadUniform("time", value);
}

void ParticuleShader::LoadLifeTimeUniform(float value)
{
	LoadUniform("lifeTime", value);
}

#pragma endregion


