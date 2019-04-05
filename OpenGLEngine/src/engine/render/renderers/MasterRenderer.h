#pragma once

#include "./GameObjectRenderer.h"
#include "./ParticuleRender.h"
#include "../framebuffers/FramBuffer.h"
#include "../shaders/classes/BasicShader.h"

class MasterRenderer
{
private:
	GameObjectRenderer m_GameObjectRender;
	ParticuleRender m_ParticuleRender;
	FrameBuffer m_TestFrameBuffer;

	BasicShader m_TestFBOShader;
	GLuint m_QuadVAO;

public:
	MasterRenderer();
	~MasterRenderer();

	void Init();
	void Render(std::vector<GameObject>& gameObjects, 
				std::vector<ParticuleSystem> & particuleSystems, 
				LightScene& lightScene, 
				Camera& camera, 
				float frameTime);	
	void CleanUp();
};