#version 410 core

layout(vertices = 4) out;

void main()
{
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

	gl_TessLevelOuter[0] = 1;
	gl_TessLevelOuter[1] = 100; /* x direction */
}
