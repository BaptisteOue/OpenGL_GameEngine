#include "OBJLoader.h"
#include "FileUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "glm/glm.hpp"


#pragma region Public API

Mesh& OBJLoader::LoadOBJ(const char* objFile)
{
	std::vector<int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvs;

	std::string line;
	
	glm::vec3 position;
	glm::vec3 uvs;
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
			file >> uvs.x >> uvs.y >> uvs.z;
			temp_uvs.push_back(uvs);
		}
		else if (line.compare("f") == 0)
		{
			file >> vertices[0] >> vertices[1] >> vertices[2];
			ParseFace(vertices, vertexIndices, uvIndices, normalIndices);
		}
	}
	
	std::vector<GLfloat> ordered_positions;
	ordered_positions.reserve(temp_positions.size() * 3);
	std::vector<GLfloat> ordered_normals;
	ordered_normals.reserve(temp_normals.size() * 3);
	std::vector<GLfloat> ordered_uvs;
	ordered_uvs.reserve(temp_uvs.size() * 2);
	std::vector<GLuint> indices;
	indices.reserve(vertexIndices.size());

	for (int i = 0; i < vertexIndices.size(); i++)
	{
		indices.push_back(i);

		int indexPos = vertexIndices[i];
		ordered_positions.push_back(-temp_positions[indexPos].x);
		ordered_positions.push_back(-temp_positions[indexPos].y);
		ordered_positions.push_back(temp_positions[indexPos].z);

		int normIndex = normalIndices[i];
		ordered_normals.push_back(-temp_normals[normIndex].x);
		ordered_normals.push_back(-temp_normals[normIndex].y);
		ordered_normals.push_back(temp_normals[normIndex].z);

		/*int texIndex = uvIndices[i];
		ordered_uvs.push_back(temp_uvs[texIndex].x);
		ordered_uvs.push_back(temp_uvs[texIndex].y);*/
	}

	Mesh* m = new Mesh();
	m->LoadMesh(ordered_positions, ordered_normals, indices);
	return *m;
}

#pragma endregion



#pragma region Private API

void OBJLoader::ParseFace(
	std::string vertices[3],
	std::vector<int>& vertexIndices,
	std::vector<int>& uvIndices,
	std::vector<int>& normalIndices)
{

	for (int i = 0; i < 3; i++)
	{
		std::stringstream ss(vertices[i]);
		std::string item[3];

		for (int j = 0; std::getline(ss, item[j], '/'); j++);

		vertexIndices.push_back(std::stoi(item[0]) - 1);
		if (!item[1].empty())
			uvIndices.push_back(std::stoi(item[1]) - 1);
		else
			uvIndices.push_back(-1);

		normalIndices.push_back(std::stoi(item[2]) - 1);
	}
}

#pragma endregion


