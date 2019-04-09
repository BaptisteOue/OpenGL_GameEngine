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
            if(length(vs_out.velocity) <= 0.1f)
            {
                vs_out.velocity = vec3(0);
                vs_out.position.y = 0.1f;
            }
            else
            {
                if(vs_out.velocity != 0)
                {
                    vs_out.position += velocity * frameTime;
                    vs_out.velocity += (acceleration + gravityForce * dt) * frameTime + gravityForce * frameTime;

                    if(vs_out.position.y <= 0)
                    {
                        vs_out.position.y = 0.1f;
                        vs_out.velocity = reflect(vs_out.velocity, vec3(0, 1, 0));
                        vs_out.velocity.x /= 1.5f;
                        vs_out.velocity.z /= 1.5f;
                        vs_out.velocity.y /= 5;

                        if(length(vs_out.velocity) < 0.5f)
                            vs_out.velocity = vec3(0);
                    }
                }
                
            }
            
        }
    }
}