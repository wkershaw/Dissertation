#version 150 core

uniform sampler2D mainTex;

in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN;

out vec4 fragColour;

void main(void)
{	

	if(textureSize(mainTex, 1).x < 1.0f) {
		fragColour = IN.colour;
	}
	else {
		fragColour = texture(mainTex, IN.texCoord) * IN.colour;
		if(fragColour.a == 0){
			discard;
		}
	}
}