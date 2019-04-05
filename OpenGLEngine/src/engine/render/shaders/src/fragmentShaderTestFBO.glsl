#version 460 core

out vec4 FragColor;

in OUT {
    vec2 texCoords;
}fs_in;

layout(binding = 0) uniform sampler2D screenTexture;

void main()
{
    float offset = 1.0f/500.0f;

    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );


    vec3 sampleTex[9];
    float kernel[9] = float[](
        4, 4, 4,
        4, -32, 4,
        4, 4, 4
    );

    // Sample around the pixel
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, fs_in.texCoords.st + offsets[i]));
    }

    // Add all the samples together
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    FragColor = vec4(col, 1.0);
}