#include "FramBuffer.h"

FrameBuffer::FrameBuffer(int width, int height)
	: m_Width{width},
	m_Height{height}
{
	
}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::Init()
{
	glGenFramebuffers(1, &m_Fbo);
}

bool FrameBuffer::BindAttachements()
{
	Bind(true);
	bool status = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	Bind(false);
	return status;
}

void FrameBuffer::Bind(bool value)
{
	if (value)
		glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::AddTexture2DColorAttachement()
{
	glGenTextures(1, &m_ColorTexture);
	glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);

	Bind(true);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTexture, 0);
	Bind(false);
}

void FrameBuffer::AddTexture2DDepthAttachement()
{
	glGenTextures(1, &m_DepthTexture);
	glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Do not repeat shadow
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Everything will be further so nothing will be shadowed

	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);

	Bind(true);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture, 0);
	Bind(false);
}

void FrameBuffer::AddRBODepthStencilAttachement()
{
	glGenRenderbuffers(1, &m_DepthStencilRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthStencilRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	Bind(true);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthStencilRBO);
	Bind(false);
}

void FrameBuffer::CleanUp()
{
	if(glIsRenderbuffer(m_DepthStencilRBO))
		glDeleteRenderbuffers(1, &m_DepthStencilRBO);
	if(glIsTexture(m_ColorTexture))
		glDeleteTextures(1, &m_ColorTexture);
	if(glIsTexture(m_DepthTexture))
		glDeleteTextures(1, &m_DepthTexture);

	glDeleteFramebuffers(1, &m_Fbo);
}

GLuint FrameBuffer::GetColorTexture()
{
	return m_ColorTexture;
}

GLuint FrameBuffer::GetDepthTexture()
{
	return m_DepthTexture;
}


