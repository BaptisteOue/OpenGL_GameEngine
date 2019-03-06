#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh
{
private:
    GLuint m_VaoID;
    int m_VertexCount;

    std::vector<GLuint> m_Vbos;
    GLuint m_EboID;

private:
    void AddData(int attribIndex, int count, std::vector<GLfloat>data);
    void AddIndices(std::vector<GLubyte>indices);
public:
    Mesh();
    ~Mesh();

    void LoadMesh(std::vector<GLfloat>& positions, std::vector<GLfloat>& colors, std::vector<GLubyte>& indices);
    void Draw();
    void CleanUp();
};