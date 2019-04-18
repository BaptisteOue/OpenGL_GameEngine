#pragma once

#include <GL/glew.h>

class FrameBuffer
{
private:
	int m_Width;
	int m_Height;
	GLuint m_Fbo;

	GLuint m_ColorTexture;
	GLuint m_DepthTexture;
	GLuint m_DepthStencilRBO;

public:
	FrameBuffer(int width, int height);
	~FrameBuffer();

	void Init();
	void AddTexture2DColorAttachement();
	void AddTexture2DDepthAttachement();
	void AddRBODepthStencilAttachement();
	bool BindAttachements();
	void Bind(bool value);
	void CleanUp();

	GLuint GetColorTexture();
	GLuint GetDepthTexture();
};