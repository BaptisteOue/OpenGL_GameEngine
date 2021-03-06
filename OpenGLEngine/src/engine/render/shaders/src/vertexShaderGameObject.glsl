#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightSpaceMatrix;

out OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
    vec2 texCoords;
    vec4 fragPosLightSpace;
} vs_out;

void main()
{
    vs_out.eye_pos = viewMatrix * modelMatrix * vec4(position, 1);
    vs_out.eye_normal = viewMatrix * modelMatrix * vec4(normal, 0);
    vs_out.texCoords = texCoords;

    // As seen from the light for shadow maping
    vs_out.fragPosLightSpace = lightSpaceMatrix * modelMatrix * vec4(position, 1);

    gl_Position = projectionMatrix * vs_out.eye_pos;
}