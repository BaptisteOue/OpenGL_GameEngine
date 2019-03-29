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
	AddUniform("cameraPos");

	AddUniform("lifeTime");
	AddUniform("maxPointSize");
	AddUniform("time");

}

void ParticuleShader::LoadCameraPosUniform(const glm::vec3 & value)
{
	LoadUniform("cameraPos", value);
}

void ParticuleShader::LoadMaxPointSizeUniform(float value)
{
	LoadUniform("maxPointSize", value);
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


