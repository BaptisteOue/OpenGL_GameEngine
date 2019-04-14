#pragma once
#include <sstream>
#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "../models/Mesh.h"
#include "../materials/Texture.h"

class Loader
{
private:
	static void ParseFace(
		std::string vertices[3],
		std::vector<int>& vertexIndices, 
		std::vector<int>& uvIndices, 
		std::vector<int>& normalIndices);
public:
	Loader() = delete;
    static Mesh& LoadOBJ(const char* objFile);
	static Texture& Load2DTexture(const char* textureFile, GLuint activeTexture = GL_TEXTURE0);
	static Texture& LoadCubeMapTexture(const char* textureFiles[6], GLuint activeTexture = GL_TEXTURE0);
};
