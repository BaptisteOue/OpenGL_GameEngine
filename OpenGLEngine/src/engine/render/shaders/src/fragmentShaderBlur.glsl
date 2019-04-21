#version 460 core

in vec2 out_TexCoord;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D brightMap;
uniform bool horizontal;

const float gaussianWeights[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
    vec2 texOffset = 1.0 / textureSize(brightMap, 0); // gets size of single texel
    vec3 result = texture(brightMap, out_TexCoord).rgb * gaussianWeights[0]; // current fragment's contribution

    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(brightMap, out_TexCoord + vec2(texOffset.x * i, 0.0)).rgb * gaussianWeights[i];
            result += texture(brightMap, out_TexCoord - vec2(texOffset.x * i, 0.0)).rgb * gaussianWeights[i];
        }
    }

    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(brightMap, out_TexCoord + vec2(0.0, texOffset.y * i)).rgb * gaussianWeights[i];
            result += texture(brightMap, out_TexCoord - vec2(0.0, texOffset.y * i)).rgb * gaussianWeights[i];
        }
    }

    fragColor = vec4(result, 1.0);
} 