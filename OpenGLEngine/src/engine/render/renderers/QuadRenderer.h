#pragma once

#include <gl/glew.h>

class QuadRenderer
{
private:
	GLfloat m_Vertices[16] = {
		// Positions	// TexCoords
		-1.0f, 1.0f,	0.0f, 1.0f,
		-1.0f, -1.0f,	0.0f, 0.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f
	};

	GLuint m_QuadVAO;

public:
	QuadRenderer();
	~QuadRenderer();

	void Init();
	void Render();
};