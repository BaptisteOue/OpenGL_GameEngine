#version 460 core


in OUT
{
    float transp;
} fs_in;

out vec4 fragColor;


void main()
{
    fragColor = vec4(fs_in.transp);
    fragColor.a *= fs_in.transp;
}