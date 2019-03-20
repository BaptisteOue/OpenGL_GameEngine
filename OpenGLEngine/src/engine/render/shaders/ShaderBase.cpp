#include "ShaderBase.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include "../utils/FileUtils.h"


#pragma region Public API


ShaderBase::ShaderBase(const char* vertexShaderPath, const char* fragmentShaderPath, const char* tessCtrlPath, const char* tessEvalPath)
	: m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath), 
	  m_TessCtrlShaderPath(tessCtrlPath), m_TessEvalShaderPath(tessEvalPath)
{

}

ShaderBase::~ShaderBase()
{

}

void ShaderBase::CreateShaderProgram()
{
	ConstructShader();
	CreateUniforms();
}

void ShaderBase::Use(bool use)
{
    glUseProgram(m_Program * (int)use);
}

void ShaderBase::CleanUp()
{
	if (glIsProgram(m_Program))
		glDeleteProgram(m_Program);
}

#pragma endregion


#pragma region Private API

void ShaderBase::AddUniform(const std::string& uniformName)
{
    GLuint uniformLocation = glGetUniformLocation(m_Program, uniformName.c_str());
    if(uniformLocation != -1)
    {
        m_Uniforms.emplace(std::pair<const std::string, GLuint>(uniformName, uniformLocation));
    }
    else
    {
        std::cout << "Can't find uniform : " << uniformName << std::endl;
    }
}

void ShaderBase::LoadUniform(const std::string& uniformName, const glm::mat4& value)
{
    glUniformMatrix4fv(m_Uniforms[uniformName], 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderBase::LoadUniform(const std::string& uniformName, const glm::vec3& value)
{
	glUniform3f(m_Uniforms[uniformName], value.x, value.y, value.z);
}

void ShaderBase::LoadUniform(const std::string& uniformName, float value)
{
	glUniform1f(m_Uniforms[uniformName], value);
}

void ShaderBase::LoadUniform(const std::string& uniformName, bool value)
{
	if(value)
		glUniform1i(m_Uniforms[uniformName], 1);
	else
		glUniform1i(m_Uniforms[uniformName], 0);
}


GLuint ShaderBase::CreateShader(GLuint shaderType, const std::string& shaderFilePath)
{
	std::string stringShaderSource = FileUtils::LoadFile(shaderFilePath);

	const GLchar* const shaderSource = stringShaderSource.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

    GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		char* error = new char[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, error);

		std::cout << error << std::endl;

		delete[] error;
		glDeleteShader(shader);
		return -1;
	}

    return shader;
}

GLuint ShaderBase::CreateVertexShader()
{
    return CreateShader(GL_VERTEX_SHADER, m_VertexShaderPath);
}

GLuint ShaderBase::CreateTessCtrlShader()
{
	return CreateShader(GL_TESS_CONTROL_SHADER, m_TessCtrlShaderPath);
}

GLuint ShaderBase::CreateTessEvalShader()
{
	return CreateShader(GL_TESS_EVALUATION_SHADER, m_TessEvalShaderPath);
}

GLuint ShaderBase::CreateFragmentShader()
{
    return CreateShader(GL_FRAGMENT_SHADER, m_FragmentShaderPath);
}


GLuint ShaderBase::CreateProgram()
{
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, m_VertexShader);
    glAttachShader(shaderProgram, m_FragmentShader);

	if (glIsShader(m_TessCtrlShader))
		glAttachShader(shaderProgram, m_TessCtrlShader);

	if (glIsShader(m_TessEvalShader))
		glAttachShader(shaderProgram, m_TessEvalShader);

    glLinkProgram(shaderProgram);

    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

        char* error = new char[maxLength];
        glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, error);
        std::cout << error << std::endl;
        delete[] error;

        glDeleteProgram(shaderProgram);
		if (glIsShader(m_TessCtrlShader))
			glDeleteShader(m_TessCtrlShader);
		if (glIsShader(m_TessEvalShader))
			glDeleteShader(m_TessEvalShader);
        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);

        return -1;
    }

	if (glIsShader(m_VertexShader))
		glDeleteShader(m_VertexShader);
	if (glIsShader(m_FragmentShader))
		glDeleteShader(m_FragmentShader);
	if (glIsShader(m_TessCtrlShader))
		glDeleteShader(m_TessCtrlShader);
	if (glIsShader(m_TessEvalShader))
		glDeleteShader(m_TessEvalShader);

    return shaderProgram;
}

#pragma endregion