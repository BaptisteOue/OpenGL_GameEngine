#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh
{
private:
    GLuint m_VaoID;
    int m_VertexCount;
	float m_TessLevelOuter;
	float m_TessLevelInner;

    std::vector<GLuint> m_Vbos;
    GLuint m_EboID;

private:
    void AddData(int attribIndex, int count, std::vector<GLfloat>data);
    void AddIndices(std::vector<GLuint>indices);
public:
    Mesh();
    ~Mesh();

    void LoadMesh(std::vector<GLfloat>& positions, std::vector<GLfloat>& normals, std::vector<GLuint>& indices);
    void Draw();
    void CleanUp();

	float GetTessLevelOuter() const;
	float GetTessLevelInner() const;

	void SetTessLevelOuter(float value);
	void SetTessLevelInner(float value);
};