#pragma once

#pragma once

#include <GL/glew.h>
#include <vector>

class ParticuleGroup
{
private:
	int m_VertexCount;
	int m_NbParticules;

	GLuint m_VaoPingPong[2];
	GLuint m_FeedbackIDs[2];
	int m_DrawBuffer = 0;

	std::vector<GLuint> m_Vbos;

private:
	void AddData(const int attribIndex, const int count, const std::vector<GLfloat>& data);
public:
	ParticuleGroup();
	~ParticuleGroup();

	void LoadParticuleGroup(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& speeds, const std::vector<GLfloat>& startTimes);
	void UpdatePass();
	void RenderPass();
	void CleanUp();

	void SetNbParticules(int nbParticules);
};