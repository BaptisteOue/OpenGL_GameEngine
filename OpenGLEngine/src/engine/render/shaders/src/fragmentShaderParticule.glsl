#version 460 core


in OUT
{
    float transp;
} fs_in;

out vec4 fragColor;


void main()
{

    if(fs_in.transp <= 0)
        discard;

    fragColor = vec4(1, 0, 1, 1);
    fragColor.a *= fs_in.transp;
}