#pragma once

#include <GL/glew.h>
#include <string>
#include <map>
#include <glm/glm.hpp>

class ShaderBase
{
protected:
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_TessCtrlShader;
	GLuint m_TessEvalShader;
	GLuint m_Program;

	std::string m_VertexShaderPath;
	std::string m_TessCtrlShaderPath;
	std::string m_TessEvalShaderPath;
	std::string m_FragmentShaderPath;

	std::map<const std::string, GLuint> m_Uniforms;

protected:
	GLuint CreateShader(GLuint shaderType, const std::string& shaderFilePath);
	GLuint CreateVertexShader();
	GLuint CreateFragmentShader();
	GLuint CreateTessCtrlShader();
	GLuint CreateTessEvalShader();
	void LinkProgram(int shaderProgram);
	GLuint CreateProgram();
	void AddUniform(const std::string& uniformName);
	void LoadUniform(const std::string& uniformName, const glm::mat4& value);
	void LoadUniform(const std::string& uniformName, const glm::vec3& value);
	void LoadUniform(const std::string& uniformName, const float value);
	void LoadUniform(const std::string& uniformName, bool value);

	void RegisterVertexShader(const char* vertexShaderPath);
	void RegisterFragmentShader(const char* fragmentShaderPath);
	void RegisterTessCtrlShader(const char* tessCtrlPath);
	void RegisterTessEvalShader(const char* tessEvalPath);

public:
	ShaderBase();
	~ShaderBase();

	void CreateShaderProgram();
	void Use(bool use);
	void CleanUp();
	virtual void CreateUniforms() = 0;
	virtual void ConstructShader() = 0;
};