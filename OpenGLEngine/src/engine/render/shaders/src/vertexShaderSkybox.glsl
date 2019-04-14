#version 460 core

layout (location = 0) in vec3 position;

out vec3 texCoords;

layout(binding = 0) uniform sampler2D materialTexture;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec4 pos = projectionMatrix * viewMatrix * vec4(position, 1.0);
    gl_Position = pos.xyww;
    texCoords = position;
}