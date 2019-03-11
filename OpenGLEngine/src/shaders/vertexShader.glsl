#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out VS_OUT
{
    vec4 world_pos;
    vec4 world_normal;
} vs_out;

void main()
{
    vs_out.world_pos = modelMatrix * vec4(position, 1);
    vs_out.world_normal = modelMatrix * vec4(normal, 0);

    gl_Position = projectionMatrix * viewMatrix * vs_out.world_pos;
}