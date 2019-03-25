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
	
	bool m_hasTextureCoords;

private:
    void AddData(const int attribIndex, const int count, const std::vector<GLfloat>& data);
    void AddIndices(const std::vector<GLuint>& indices);
public:
    Mesh();
    ~Mesh();

    void LoadMesh(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& normals, const std::vector<GLfloat>& texCoords, const std::vector<GLuint>& indices);
    void Draw();
    void CleanUp();

	bool HasTextureCoords() const;
};