#include "ParticuleFeedForwardShader.h"

ParticuleFeedForwardShader::ParticuleFeedForwardShader()
	: ShaderBase("ParticuleShaderFeedForward")
{
	RegisterVertexShader(ParticuleFeedForwardShader::VERTEX_SHADER);
}

ParticuleFeedForwardShader::~ParticuleFeedForwardShader()
{
}

void ParticuleFeedForwardShader::ConstructShader()
{
	m_VertexShader = CreateVertexShader();
	m_Program = CreateProgram();
	glTransformFeedbackVaryings(m_Program, 3, OUTPUT_NAMES, GL_SEPARATE_ATTRIBS);
	LinkProgram(m_Program);
}

void ParticuleFeedForwardShader::CreateUniforms()
{
	AddUniform("center");
	AddUniform("acceleration");
	AddUniform("gravityForce");
	AddUniform("lifeTime");
	AddUniform("time");
	AddUniform("frameTime");
}

void ParticuleFeedForwardShader::LoadLifeTimeUniform(float value)
{
	LoadUniform("lifeTime", value);
}

void ParticuleFeedForwardShader::LoadSimulationTimeUniform(float value)
{
	LoadUniform("time", value);
}


void ParticuleFeedForwardShader::LoadFrameTimeUniform(float value)
{
	LoadUniform("frameTime", value);
}

void ParticuleFeedForwardShader::LoadGravityForceUniform(const glm::vec3 & value)
{
	LoadUniform("gravityForce", value);
}

void ParticuleFeedForwardShader::LoadAccelerationUniform(const glm::vec3 & value)
{
	LoadUniform("acceleration", value);
}

void ParticuleFeedForwardShader::LoadCenterUniform(const glm::vec3 & value)
{
	LoadUniform("center", value);
}
