#version 330 core

uniform float particleSize = 0.1f;

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in Vertex {
	vec4 colour;
	vec2 texCoord;
	float visibility;
} IN[];

out Vertex {
	vec4 colour;
	vec2 texCoord;
	float visibility;
} OUT;

void main(){

	for(int i=0;i<gl_in.length();++i){
		OUT.visibility = IN[i].visibility;
		OUT.colour = IN[i].colour;
		gl_Position = gl_in[i].gl_Position;
		gl_Position.x += particleSize;
		gl_Position.y += particleSize;
		OUT.texCoord = vec2(1,0);
		EmitVertex();

		gl_Position = gl_in[i].gl_Position;
		gl_Position.x -= particleSize;
		gl_Position.y += particleSize;
		OUT.texCoord = vec2(0,0);
		EmitVertex();

		gl_Position = gl_in[i].gl_Position;
		gl_Position.x += particleSize;
		gl_Position.y -= particleSize;
		OUT.texCoord = vec2(1,1);
		EmitVertex();

		gl_Position = gl_in[i].gl_Position;
		gl_Position.x -= particleSize;
		gl_Position.y -= particleSize;
		OUT.texCoord = vec2(0,1);
		EmitVertex();

		EndPrimitive();
	}
}