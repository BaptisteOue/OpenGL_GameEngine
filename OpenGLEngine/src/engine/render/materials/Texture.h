#pragma once

#include <GL/glew.h>

class Texture
{

private:
	GLuint m_TextureID;
	GLuint m_ActveTexture;

public:
	Texture(GLuint textureID, GLuint activeTexture);
	~Texture();

	const GLuint GetTextureID() const;
	const GLuint GetActiveTexture() const;
};