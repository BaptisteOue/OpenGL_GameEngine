#pragma once

#include "./GameObjectRenderer.h"
#include "./ParticuleRender.h"

class MasterRenderer
{
private:
	GameObjectRenderer m_GameObjectRender;
	ParticuleRender m_ParticuleRender;

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