#version 460 core


in OUT
{
    float transp;
} fs_in;

out vec4 fragColor;


void main()
{
    if(fs_in.transp <= 0.3)
        discard;
    fragColor = vec4(0.0f, 0.4f, 0.6f, fs_in.transp);
}