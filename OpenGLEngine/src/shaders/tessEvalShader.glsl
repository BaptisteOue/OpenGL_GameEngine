#version 460 core

layout(triangles, fractional_even_spacing, ccw) in;

in TESS_CTRL_OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
} tess_in[];

out OUT
{
    vec4 eye_pos;
    vec4 eye_normal;
} tess_out;


vec4 interpole(vec4 p0, vec4 p1, vec4 p2)
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    float w = gl_TessCoord.z;

    return p0 * u + p1 * v + p2 *w;

}

void main(void)
{
    gl_Position = interpole(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);
    gl_PointSize = gl_in[0].gl_PointSize;

    tess_out.eye_pos = interpole(tess_in[0].eye_pos, tess_in[1].eye_pos, tess_in[2].eye_pos);
    tess_out.eye_normal = interpole(tess_in[0].eye_normal, tess_in[1].eye_normal, tess_in[2].eye_normal);
}