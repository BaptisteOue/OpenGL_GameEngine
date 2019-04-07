#include "ShadowMapShader.h"


ShadowMapShader::ShadowMapShader()
	: BasicShader()
{
	RegisterVertexShader(ShadowMapShader::VERTEX_SHADER);
	RegisterFragmentShader(ShadowMapShader::FRAGMENT_SHADER);
}

ShadowMapShader::~ShadowMapShader()
{
}

void ShadowMapShader::CreateUniforms()
{
	AddUniform("lightSpaceMatrix");
	AddUniform("modelMatrix");
}

void ShadowMapShader::LoadUniforms(glm::mat4 lightSpaceMatrix, glm::mat4 modelMatrix)
{
	LoadUniform("lightSpaceMatrix", lightSpaceMatrix);
	LoadUniform("modelMatrix", modelMatrix);
}

