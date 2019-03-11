#pragma once
#include <sstream>
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "../models/Mesh.h"

class OBJLoader
{
private:
	static void ParseFace(
		std::string vertices[3],
		std::vector<int>& vertexIndices, 
		std::vector<int>& uvIndices, 
		std::vector<int>& normalIndices);
public:
	OBJLoader() = delete;
    static Mesh& LoadOBJ(const char* objFile);
};
