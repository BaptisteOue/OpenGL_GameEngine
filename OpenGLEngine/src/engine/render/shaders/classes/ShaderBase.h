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
	GLuint m_GeometryShader;
	GLuint m_TessCtrlShader;
	GLuint m_TessEvalShader;
	GLuint m_Program;
	std::string m_ShaderName;

	std::string m_VertexShaderPath;
	std::string m_TessCtrlShaderPath;
	std::string m_TessEvalShaderPath;
	std::string m_GeometryShaderPath;
	std::string m_FragmentShaderPath;

	std::map<const std::string, GLuint> m_Uniforms;

protected:
	GLuint CreateShader(GLuint shaderType, const std::string& shaderFilePath);
	GLuint CreateVertexShader();
	GLuint CreateFragmentShader();
	GLuint CreateGeometryShader();
	GLuint CreateTessCtrlShader();
	GLuint CreateTessEvalShader();
	void LinkProgram(int shaderProgram);
	GLuint CreateProgram();
	void AddUniform(const std::string& uniformName);
	void LoadUniform(const std::string& uniformName, const glm::mat4& value);
	void LoadUniform(const std::string& uniformName, const glm::vec3& value);
	void LoadUniform(const std::string& uniformName, float value);
	void LoadUniform(const std::string& uniformName, int value);
	void LoadUniform(const std::string& uniformName, bool value);

	void RegisterVertexShader(const char* vertexShaderPath);
	void RegisterFragmentShader(const char* fragmentShaderPath);
	void RegisterGeometryShader(const char* geometryShaderPath);
	void RegisterTessCtrlShader(const char* tessCtrlPath);
	void RegisterTessEvalShader(const char* tessEvalPath);

public:
	ShaderBase(const std::string& shaderName);
	~ShaderBase();

	void CreateShaderProgram();
	void Use(bool use);
	void CleanUp();
	virtual void CreateUniforms() = 0;
	virtual void ConstructShader() = 0;
};
