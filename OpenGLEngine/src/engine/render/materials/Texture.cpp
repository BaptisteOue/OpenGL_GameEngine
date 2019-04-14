#include "Texture.h"


Texture::Texture()
	: Texture{0, 0}
{
}

Texture::Texture(GLuint textureID, GLuint activeTexture)
	: m_TextureID(textureID), m_ActveTexture(activeTexture)
{
}

Texture::~Texture()
{
}

const GLuint Texture::GetTextureID() const
{
	return m_TextureID;
}

const GLuint Texture::GetActiveTexture() const
{
	return m_ActveTexture;
}
