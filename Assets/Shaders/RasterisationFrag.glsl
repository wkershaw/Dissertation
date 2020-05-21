#version 150 core

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

	if(textureSize(mainTex, 1).x < 1.0f) {
		fragColour = mix(skyColour,IN.colour,IN.visibility);
		//fragColour = IN.colour;
	}
	else {
		fragColour = texture(mainTex, IN.texCoord) * IN.colour;
		if(fragColour.a == 0){
			discard;
		}
	}
}