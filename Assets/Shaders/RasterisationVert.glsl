#version 400 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);
uniform float fogDensity	= 0.02f;
uniform float fogGradient	= 1.5f;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;

out Vertex
{
	vec4 colour;
	vec2 texCoord;
	float visibility;
} OUT;


void main(void)
{
	vec4 objectCameraPosition = viewMatrix * modelMatrix * vec4(position, 1.0);
	mat4 mvp 		= projMatrix * viewMatrix * modelMatrix;
	gl_Position		= mvp * vec4(position, 1.0);

	float distance = length(objectCameraPosition.xyz);
	
	OUT.visibility = exp(-pow((distance*fogDensity),fogGradient));	

	OUT.texCoord	= texCoord;
	OUT.colour	= colour;
}