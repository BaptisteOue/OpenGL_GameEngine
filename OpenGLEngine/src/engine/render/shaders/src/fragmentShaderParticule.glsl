#version 460 core


in GS_OUT
{
    float transp;
    vec3 color;
} fs_in;

out vec4 fragColor;


void main()
{
    fragColor = vec4(fs_in.color, fs_in.transp);
}