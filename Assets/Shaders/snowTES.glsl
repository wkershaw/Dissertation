#version 400

layout(quads, cw) in;

uniform sampler2D heightMap;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float time;
uniform float fogDensity	= 0.02f;
uniform float fogGradient	= 1.5f;
uniform float snowSpeed		= 0;

in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN[];

out Vertex
{
	vec4 colour;
	vec2 texCoord;
	float visibility;
} OUT;


vec3 QuadMixVec3(vec3 a, vec3 b, vec3 c, vec3 d){
	vec3 p0 = mix(a,c, gl_TessCoord.x);
	vec3 p1 = mix(b,d, gl_TessCoord.x);

	return mix(p0, p1, gl_TessCoord.y);
}

vec2 QuadMixVec2(vec2 a, vec2 b, vec2 c, vec2 d){
	vec2 p0 = mix(a,c, gl_TessCoord.x);
	vec2 p1 = mix(b,d, gl_TessCoord.x);

	return mix(p0, p1, gl_TessCoord.y);
}

vec4 QuadMixVec4(vec4 a, vec4 b, vec4 c, vec4 d){
	vec4 p0 = mix(a,c, gl_TessCoord.x);
	vec4 p1 = mix(b,d, gl_TessCoord.x);

	return mix(p0, p1, gl_TessCoord.y);
}

void main()
{
	vec3 combinedPos = QuadMixVec3(gl_in[0].gl_Position.xyz,
					gl_in[1].gl_Position.xyz,
					gl_in[2].gl_Position.xyz,
					gl_in[3].gl_Position.xyz);
	OUT.texCoord = QuadMixVec2(IN[0].texCoord,
					IN[1].texCoord,
					IN[2].texCoord,
					IN[3].texCoord);
	OUT.colour = QuadMixVec4(IN[0].colour,
					IN[1].colour,
					IN[2].colour,
					IN[3].colour);

	
	vec4 worldPos = modelMatrix * vec4(combinedPos, 1);

	vec4 objectCameraPosition = viewMatrix * worldPos;
	float distance = length(objectCameraPosition.xyz);
	OUT.visibility = exp(-pow((distance*fogDensity),fogGradient));

	float height = max(texture(heightMap, OUT.texCoord).x,0.02);
	worldPos.y += min(height*time*snowSpeed,height*0.5);
	gl_Position = projMatrix * viewMatrix * worldPos;


}	