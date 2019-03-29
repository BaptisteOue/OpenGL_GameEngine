#include "ParticuleShader.h"


#pragma region Public API

ParticuleShader::ParticuleShader()
	: BasicShader()
{
	RegisterVertexShader(ParticuleShader::VERTEX_SHADER);
	RegisterFragmentShader(ParticuleShader::FRAGMENT_SHADER);
}

ParticuleShader::~ParticuleShader()
{
}


void ParticuleShader::CreateUniforms()
{
	AddUniform("modelMatrix");
	AddUniform("viewMatrix");
	AddUniform("projectionMatrix");

	AddUniform("gravityForce");
	AddUniform("lifeTime");
	AddUniform("time");
}

void ParticuleShader::LoadLifeTimeUniform(float value)
{
	LoadUniform("lifeTime", value);
}

void ParticuleShader::LoadSimulationTimeUniform(float value)
{
	LoadUniform("time", value);
}

void ParticuleShader::LoadGravityForceUniform(const glm::vec3 & value)
{
	LoadUniform("gravityForce", value);
}

#pragma endregion


