#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include "ShaderBase.h"
#include "../utils/FileUtils.h"


#pragma region Public API

ShaderBase::ShaderBase(const char* vertexShaderPath, const char* fragmentShaderPath)
    : m_VertexShaderPath(vertexShaderPath), m_FragmentShaderPath(fragmentShaderPath)
{
}

ShaderBase::~ShaderBase()
{

}

void ShaderBase::CreateShaderProgram()
{
    m_VertexShader = CreateVertexShader();
    m_FragmentShader = CreateFragmentShader();
    m_Program = CreateProgram();

	CreateUniforms();
}

void ShaderBase::Use(bool use)
{
    glUseProgram(m_Program * (int)use);
}

#pragma endregion


#pragma region Private API

void ShaderBase::AddUniform(const char* uniformName)
{
    GLuint uniformLocation = glGetUniformLocation(m_Program, uniformName);
    if(uniformLocation != -1)
    {
        m_Uniforms.emplace(std::pair<const char* , GLuint>(uniformName, uniformLocation));
    }
    else
    {
        std::cout << "Can't find uniform : " << uniformName << std::endl;
    }
}

void ShaderBase::LoadUniform(const char* uniformName, glm::mat4& value)
{
    glUniformMatrix4fv(m_Uniforms[uniformName], 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderBase::LoadUniform(const char * uniformName, glm::vec3 value)
{
	glUniform3f(m_Uniforms[uniformName], value.x, value.y, value.z);
}

void ShaderBase::LoadUniform(const char * uniformName, float value)
{
	glUniform1f(m_Uniforms[uniformName], value);
}

GLuint ShaderBase::CreateShader(GLuint shaderType, std::string& shaderFilePath)
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

GLuint ShaderBase::CreateFragmentShader()
{
    return CreateShader(GL_FRAGMENT_SHADER, m_FragmentShaderPath);
}

GLuint ShaderBase::CreateProgram()
{
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, m_VertexShader);
    glAttachShader(shaderProgram, m_FragmentShader);

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
        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);

        return -1;
    }

    return shaderProgram;
}

#pragma endregion