#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 out_color;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);
    out_color = vec4(color, 1);
}