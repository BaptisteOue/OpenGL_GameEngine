#pragma once

#include <GL/glew.h>
#include <vector>

class FrameBuffer
{
private:
	int m_Width;
	int m_Height;
	GLuint m_Fbo;

	int m_NbColorAttachements;

	std::vector<GLuint> m_ColorTextures;
	GLuint m_DepthTexture;
	GLuint m_DepthStencilRBO;

public:
	FrameBuffer(int width, int height);
	~FrameBuffer();

	void Init();
	void AddTexture2DColorAttachement(int attachmentIndex = 0);
	void AddTexture2DDepthAttachement();
	void AddRBODepthStencilAttachement();
	bool BindAttachements();
	void Bind(bool value);
	void CleanUp();

	GLuint GetColorTexture(int index);
	GLuint GetDepthTexture();
};