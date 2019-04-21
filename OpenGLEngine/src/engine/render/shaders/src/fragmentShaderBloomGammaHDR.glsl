#version 460 core

in vec2 out_TexCoord;

layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D hdrBuffer;
layout(binding = 1) uniform sampler2D blurBuffer;

uniform float gamma;

void main()
{
    vec3 hdrColor = texture(hdrBuffer, out_TexCoord).rgb;
    vec3 bloomColor = texture(blurBuffer, out_TexCoord).rgb;

    hdrColor += bloomColor; // additive blending

    // HDR tone mapping
    vec3 result = hdrColor / (hdrColor + vec3(1.0));
    
    // Gama correction       
    result = pow(result, vec3(1.0 / gamma));

    fragColor = vec4(result, 1.0);
}