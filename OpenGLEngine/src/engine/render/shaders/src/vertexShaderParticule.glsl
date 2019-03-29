#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in float startTime;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPos;

uniform float maxPointSize;
uniform float lifeTime;
uniform float time;

out OUT
{
    float transp;
} vs_out;

void main()
{

    vec3 pos = (modelMatrix * vec4(position, 1)).xyz;

    gl_PointSize = maxPointSize / length(pos - cameraPos);
    gl_Position = projectionMatrix * viewMatrix * vec4(pos, 1);

    if(time < startTime)
    {
        vs_out.transp = 0;
    }
    else
    {
        float dt = time - startTime;
        vs_out.transp = 1 - dt / lifeTime;
    }
}