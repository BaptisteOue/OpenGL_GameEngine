#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
} vs_out;

void main()
{
    vs_out.eye_pos = viewMatrix * modelMatrix * vec4(position, 1);
    vs_out.eye_normal = viewMatrix * modelMatrix * vec4(normal, 0);

    gl_Position = projectionMatrix * vs_out.eye_pos;
}