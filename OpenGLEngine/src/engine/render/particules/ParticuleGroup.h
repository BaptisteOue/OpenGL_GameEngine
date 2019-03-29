#pragma once

#pragma once

#include <GL/glew.h>
#include <vector>

class ParticuleGroup
{
private:
	GLuint m_VaoIDs[1];
	int m_VertexCount;
	int m_NbParticules;
	std::vector<GLuint> m_Vbos;

private:
	void AddData(const int attribIndex, const int count, const std::vector<GLfloat>& data);
public:
	ParticuleGroup();
	~ParticuleGroup();

	void LoadParticuleGroup(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& speeds, const std::vector<GLfloat>& startTimes);
	void Draw() const;
	void CleanUp();

	void SetNbParticules(int nbParticules);
};