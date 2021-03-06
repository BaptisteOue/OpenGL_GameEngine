#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in float startTime;

uniform float lifeTime;
uniform float time;

out VS_OUT
{
    vec4 relativePos;
    float transp;
} vs_out;

void main()
{

    vs_out.relativePos =  vec4(position, 1);

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