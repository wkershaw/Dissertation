#version 400 core
layout(vertices = 4) out;
in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN[];

out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT[];

void main()
{
	gl_TessLevelInner[0] = 32;
	gl_TessLevelInner[1] = 32;
	gl_TessLevelOuter[0] = 32;
	gl_TessLevelOuter[1] = 32;
	gl_TessLevelOuter[2] = 32;
	gl_TessLevelOuter[3] = 32;

	OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;
	OUT[gl_InvocationID].colour = IN[gl_InvocationID].colour;

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}