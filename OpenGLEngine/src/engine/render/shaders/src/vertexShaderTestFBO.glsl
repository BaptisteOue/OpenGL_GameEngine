#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out OUT {
    vec2 texCoords;
}vs_out;

void main()
{
    gl_Position = vec4(position, 0.0f, 1.0f);
    vs_out.texCoords = texCoords;
}