#version 460 core

in vec3 texCoords;

out vec4 fragColor;

layout(binding = 0) uniform samplerCube cubeMap;

void main()
{
    fragColor = texture(cubeMap, texCoords);
}