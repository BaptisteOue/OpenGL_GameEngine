#include "OBJLoader.h"
#include "FileUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <memory>
#include "glm/glm.hpp"


#pragma region Public API

Mesh& OBJLoader::LoadOBJ(const char* objFile)
{
	std::ifstream file(objFile);

	if (!file.is_open())
	{
		std::cout << "Can't open " << objFile << std::endl;
	}

	std::string line;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<Face> faces;

	// For each line
	while (std::getline(file, line))
	{
		std::stringstream ss(line);

		//Check line begining
		if (line.rfind("v ", 0) == 0)
		{
			// Get each component of the line
			FillBuffer<glm::vec3>(ss, positions);
		}
		else if (line.rfind("vn ", 0) == 0)
		{
			// Get each component of the line
			FillBuffer<glm::vec3>(ss, normals);
		}
		else if (line.rfind("vt ", 0) == 0)
		{
			// Get each component of the line
			FillBuffer<glm::vec2>(ss, texCoords);
		}

		// Break loop to process faces
		else if (line.rfind("f ", 0) == 0)
		{
			if (line.rfind("f ", 0) == 0)
			{
				faces.emplace_back(ss);
			}
		}
	}

	return ProcessFaces(faces, positions, texCoords, normals);
}

#pragma endregion



#pragma region Private API


Mesh& OBJLoader::ProcessFaces(
	std::vector<Face>faces,
	std::vector<glm::vec3>positions,
	std::vector<glm::vec2>texCoords,
	std::vector<glm::vec3>normals)
{
	Mesh* mesh = new Mesh();

	std::vector<float> orderedPositions(positions.size() * 3);
	std::vector<float> orderedTexCoords(texCoords.size() * 2);
	std::vector<float> orderedNormals(normals.size() * 3);
	std::vector<GLuint> indices(faces.size() * 3);

	
	// Copy "as is" positions
	int i = 0;
	for (glm::vec3 pos : positions)
	{
		orderedPositions[i * 3] = pos.x;
		orderedPositions[i * 3 + 1] = -pos.y;
		orderedPositions[i * 3 + 2] = pos.z;
		i++;
	}

	i = 0;
	for (Face f : faces) 
	{
		for (auto v : f.m_Vertices) 
		{
			int posIndex = v->m_PosIndex;
			indices[i++] = posIndex;

			if (v->m_TexIndex != v->UNDEFINED)
			{
				orderedTexCoords[posIndex * 2] = texCoords[v->m_TexIndex].x;
				orderedTexCoords[posIndex * 2 + 1] = texCoords[v->m_TexIndex].y;
			}

			if (v->m_NormIndex != v->UNDEFINED)
			{
				orderedNormals[posIndex * 3] = normals[v->m_NormIndex].x;
				orderedNormals[posIndex * 3 + 1] = normals[v->m_NormIndex].y;
				orderedNormals[posIndex * 3 + 2] = normals[v->m_NormIndex].z;
			}
		}
	}

	mesh->LoadMesh(orderedPositions, indices);

	return *mesh;
}

OBJLoader::Face::Face(std::stringstream& ss)
{
	std::string item;
	std::vector<std::string> splitedLine;

	// Get each vertex
	for (int i = 0; std::getline(ss, item, ' '); i++)
	{
		if (i != 0)
		{
			m_Vertices[i - 1] = std::make_shared<Vertex>(item);
		}
	}
}

OBJLoader::Face::~Face()
{
}

OBJLoader::Vertex::Vertex(std::string & item)
	: m_PosIndex(UNDEFINED), m_NormIndex(UNDEFINED), m_TexIndex(UNDEFINED)
{
	std::stringstream ss(item);
	for (int i = 0; std::getline(ss, item, '/'); i++)
	{
		if (!item.empty())
		{
			if (i == 0)
				m_PosIndex = std::stoi(item) - 1;
			else if(i == 1)
				m_TexIndex = std::stoi(item) - 1;
			else if (i == 2)
				m_NormIndex = std::stoi(item) - 1;
		}
	}
}

OBJLoader::Vertex::~Vertex()
{
}

#pragma endregion


