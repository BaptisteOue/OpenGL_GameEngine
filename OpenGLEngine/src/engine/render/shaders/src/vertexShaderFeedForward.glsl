#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in float startTime;
layout (location = 2) in vec3 velocity;
layout (location = 3) in vec3 initialVelocity;


uniform float lifeTime;
uniform float time;
uniform vec3 acceleration;
uniform vec3 gravityForce;
uniform float frameTime;

out OUT {
    vec3 position;
    float startTime;
    vec3 velocity;
    float transp;
}vs_out;

void main()
{
    vs_out.position = position;
    vs_out.startTime = startTime;
    vs_out.velocity = velocity;


    if(time >= startTime)   // Particle doesn't exist until the start time
    {
        float dt = time - startTime;

        if(dt >= lifeTime)  // Re-use particle when it dies
        {
            vs_out.position = vec3(0);
            vs_out.velocity = initialVelocity;
            vs_out.startTime = time;
        }
        else    // Update particule position
        {
            vs_out.position += velocity * frameTime;
            vs_out.velocity += (acceleration + gravityForce) * frameTime;
        }

        vs_out.transp = 1.0 - dt / lifeTime;
    }
}