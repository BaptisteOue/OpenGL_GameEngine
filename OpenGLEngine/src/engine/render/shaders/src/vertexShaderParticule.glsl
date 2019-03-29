#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 speed;
layout (location = 2) in float startTime;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 gravityForce;
uniform float lifeTime;
uniform float time;

out OUT
{
    float transp;
} vs_out;

void main()
{

    vec3 pos = position;

    if(time >= startTime)
    {
        float dt = time - startTime;

        if(dt < lifeTime)
        {
            pos += speed * dt + gravityForce * dt * dt;
        }

        vs_out.transp = 1.0 - dt / lifeTime;
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
}