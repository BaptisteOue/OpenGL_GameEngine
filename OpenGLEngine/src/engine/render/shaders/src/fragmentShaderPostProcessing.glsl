#version 460 core

in vec2 out_TexCoord;

out vec4 fragColor;

layout(location = 0) uniform sampler2D hdrBuffer;
uniform float gamma;

void main()
{
    vec3 hdrColor = texture(hdrBuffer, out_TexCoord).rgb;
  
    // reinhard tone mapping
    vec3 mapped = hdrColor / (hdrColor + vec3(1.0));

    // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    fragColor = vec4(mapped, 1.0);
} 