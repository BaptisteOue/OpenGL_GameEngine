#pragma once
#include <sstream>
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "../models/Mesh.h"

class OBJLoader
{
private:

	class Face;
	class Vertex;

private:
	template<typename T>
	static void FillBuffer(std::stringstream& ss, std::vector<T>& buffer, char delim = ' ');
	static Mesh& ProcessFaces(
		std::vector<Face>faces,
		std::vector<glm::vec3>positions,
		std::vector<glm::vec2>texCoords,
		std::vector<glm::vec3>normals);
    
public:
    OBJLoader() = delete;

    static Mesh& LoadOBJ(const char* objFile);
};

class OBJLoader::Face
{
public:
	const int UNDEFINED = -1;
	std::shared_ptr<Vertex> m_Vertices[3];
public:
	Face(std::stringstream& ss);
	~Face();
};

class OBJLoader::Vertex
{
public:
	const int UNDEFINED = -1;
	int m_PosIndex;
	int m_TexIndex;
	int m_NormIndex;
public:
	Vertex(std::string& item);
	~Vertex();
};

template<typename T>
void OBJLoader::FillBuffer(std::stringstream& ss, std::vector<T>& buffer, char delim)
{
	std::string item;
	std::vector<float> splitedLine;

	// Get each component of the line
	for (int i = 0; std::getline(ss, item, delim); i++)
	{
		if (i != 0)
		{
			if (item.empty())
				item = "-1";
			splitedLine.emplace_back(std::stof(item));
		}	
	}

	// Copy the data into the buffer
	T* vec = reinterpret_cast<T*>(splitedLine.data());
	buffer.emplace_back(*vec);
}

