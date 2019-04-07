#include "MasterRenderer.h"
#include <iostream>
#include "../maths/Transformations.h"

MasterRenderer::MasterRenderer()
	: m_GameObjectRender(),
	m_ParticuleRender()
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Init()
{
	m_GameObjectRender.Init();
	m_ParticuleRender.Init();
}

void MasterRenderer::Render(std::vector<GameObject>& gameObjects,
							std::vector<ParticuleSystem>& particuleSystems,
							LightScene & lightScene, 
							Camera & camera, 
							float frameTime)
{
	m_GameObjectRender.Render(gameObjects, lightScene, camera);
	m_ParticuleRender.Render(particuleSystems, lightScene, camera, frameTime);
}

void MasterRenderer::CleanUp()
{
	m_GameObjectRender.CleanUp();
	m_ParticuleRender.CleanUp();
}