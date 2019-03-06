#pragma once

#include <GL/glew.h>
#include <string>
#include <map>
#include <glm/glm.hpp>

class ShaderProgram
{
private:
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_Program;

	std::string m_VertexShaderPath;
	std::string m_FragmentShaderPath;

	std::map<const char*, GLuint> m_Uniforms;

private:
	GLuint CreateShader(GLuint shaderType, std::string& shaderFilePath);
	GLuint CreateVertexShader();
	GLuint CreateFragmentShader();
	GLuint CreateProgram();
	void AddUniform(const char* uniformName);
	void LoadUniform(const char* uniformName, glm::mat4& value);

public:
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();

	void CreateShaderProgram();
	void LoadMatricesUniforms(glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projectionMatrix);
	void Use(bool use);
};
