#version 400 core

uniform sampler2D 	mainTex;

in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN;

out vec4 fragColor;

void main(void)
{
	if(textureSize(mainTex, 0).x < 1) {
		fragColor = IN.colour;
	}
	else {
		float alpha = texture(mainTex, IN.texCoord).r;
		if(alpha < 0.00000001f) {
			discard;
		}
		fragColor = vec4(1,1,1,alpha);
	}
}