#version 460 core

layout(vertices = 3) out;

in OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
} tess_in[];

out TESS_CTRL_OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
} tess_out[];

uniform float tessLevelOuter;
uniform float tessLevelInner;


void main(void)
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    gl_out[gl_InvocationID].gl_PointSize = gl_in[gl_InvocationID].gl_PointSize;

    tess_out[gl_InvocationID].eye_pos = tess_in[gl_InvocationID].eye_pos;
    tess_out[gl_InvocationID].eye_normal = tess_in[gl_InvocationID].eye_normal;

    gl_TessLevelOuter[0] = tessLevelOuter;
    gl_TessLevelOuter[1] = tessLevelOuter;
    gl_TessLevelOuter[2] = tessLevelOuter;

	gl_TessLevelInner[0] = tessLevelInner;
}