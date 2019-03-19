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

	std::map<const char*, GLuint> m_Uniforms;

protected:
	GLuint CreateShader(GLuint shaderType, const std::string& shaderFilePath);
	GLuint CreateVertexShader();
	GLuint CreateFragmentShader();
	GLuint CreateTessCtrlShader();
	GLuint CreateTessEvalShader();
	GLuint CreateProgram();
	void AddUniform(const char* uniformName);
	void LoadUniform(const char* uniformName, const glm::mat4& value);
	void LoadUniform(const char* uniformName, const glm::vec3& value);
	void LoadUniform(const char* uniformName, const float value);

public:
	ShaderBase(const char* vertexShaderPath = "", const char* fragmentShaderPath = "",
				const char* tessCtrlPath = "", const char* tessEvalPath = "");
	~ShaderBase();

	void CreateShaderProgram();
	void Use(bool use);
	void CleanUp();
	virtual void CreateUniforms() = 0;
	virtual void ConstructShader() = 0;
};