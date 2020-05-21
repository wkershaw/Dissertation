#version 400 core

uniform sampler2D mainTex;

in Vertex
{
	vec4 colour;
	vec2 texCoord;
	float visibility;
} IN;

out vec4 fragColour;

const vec4 skyColour = vec4(0.25f, 0.35f, 0.45f, 1);

void main(void)
{
	fragColour = mix(skyColour,IN.colour,IN.visibility);
	//fragColour = mix(skyColour,IN.colour*texture(mainTex,IN.texCoord),IN.visibility);
	//fragColour.w = texture(mainTex,IN.texCoord).x + 0.1f;


}