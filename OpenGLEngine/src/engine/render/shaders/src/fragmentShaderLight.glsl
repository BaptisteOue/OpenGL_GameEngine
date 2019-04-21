#version 460 core

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 brightColor;

uniform vec3 lightColor;

void main()
{
    fragColor = vec4(lightColor, 1);

    // Add brightColor for the bloom pass
    brightColor = fragColor;
}