#pragma once

#include "../core/Camera.h"
#include "../models/Mesh.h"
#include "../materials/Texture.h"
#include "../shaders/classes/SkyboxShader.h"
#include "../core/Camera.h"

class SkyboxRenderer
{
private:
	const char* TEXTURES[6]{ "./res/posx.jpg",
							 "./res/negx.jpg", 
							 "./res/posy.jpg", 
							 "./res/negy.jpg", 
							 "./res/posz.jpg", 
							 "./res/negz.jpg" };

	SkyboxShader m_SkyboxShader;
	Mesh m_CubeMesh;
	Texture m_CubeMap;

public:
	SkyboxRenderer();
	~SkyboxRenderer();

	void Init();
	void Render(Camera& camera);
	void CleanUp();

};