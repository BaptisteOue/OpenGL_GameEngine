#include "Loader.h"
#include "FileUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "glm/glm.hpp"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


#pragma region Public API

Mesh& Loader::LoadOBJ(const char* objFile)
{
	std::vector<int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvs;

	std::string line;
	
	glm::vec3 position;
	glm::vec2 uvs;
	glm::vec3 normal;
	std::string vertices[3];

	std::ifstream file(objFile);

	if (!file.is_open())
	{
		std::cout << "Can't open " << objFile << std::endl;
	}

	while (file >> line)
	{
		if (line.compare("v") == 0)
		{
			file >> position.x >> position.y >> position.z;
			temp_positions.push_back(position);
		}
		else if (line.compare("vn") == 0)
		{
			file >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (line.compare("vt") == 0)
		{
			file >> uvs.x >> uvs.y;
			temp_uvs.push_back(uvs);
		}
		else if (line.compare("f") == 0)
		{
			file >> vertices[0] >> vertices[1] >> vertices[2];
			ParseFace(vertices, vertexIndices, uvIndices, normalIndices);
		}
	}

	std::vector<GLfloat> ordered_positions;
	std::vector<GLfloat> ordered_normals;
	std::vector<GLfloat> ordered_uvs;
	std::vector<GLfloat> ordered_tangents;
	std::vector<GLuint> indices;

	for (int i = 0; i < vertexIndices.size(); i++)
	{
		indices.push_back(i);

		int indexPos = vertexIndices[i];
		ordered_positions.push_back(temp_positions[indexPos].x);
		ordered_positions.push_back(temp_positions[indexPos].y);
		ordered_positions.push_back(temp_positions[indexPos].z);

		int normIndex = normalIndices[i];
		ordered_normals.push_back(temp_normals[normIndex].x);
		ordered_normals.push_back(temp_normals[normIndex].y);
		ordered_normals.push_back(temp_normals[normIndex].z);

		int texIndex = uvIndices[i];
		if (texIndex != -1)
		{
			ordered_uvs.push_back(temp_uvs[texIndex].x);
			ordered_uvs.push_back(temp_uvs[texIndex].y);
		}
	}

	file.close();

	Mesh* m = new Mesh();
	m->LoadMesh(ordered_positions, ordered_normals, ordered_uvs, indices);
	return *m;
}

Texture& Loader::LoadTexture(const char * textureFile, GLuint activeTexture)
{
	Texture* texture = nullptr;
	GLuint textureID;

	glGenTextures(1, &textureID);
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		texture = new Texture(textureID, activeTexture);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	return *texture;
}

#pragma endregion



#pragma region Private API

void Loader::ParseFace(
	std::string vertices[3],
	std::vector<int>& vertexIndices,
	std::vector<int>& uvIndices,
	std::vector<int>& normalIndices)
{
	std::string item[3];
	std::stringstream ss;

	for (int i = 0; i < 3; i++)
	{
		ss << vertices[i];

		for (int j = 0; std::getline(ss, item[j], '/'); j++);

		vertexIndices.push_back(std::stoi(item[0]) - 1);
		if (!item[1].empty())
			uvIndices.push_back(std::stoi(item[1]) - 1);
		else
			uvIndices.push_back(-1);

		normalIndices.push_back(std::stoi(item[2]) - 1);

		ss.clear();
	}
}
#pragma endregion


