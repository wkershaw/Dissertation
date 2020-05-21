#include "Snow.h"
#include "Draw.h";

using namespace NCL::CSC3223;

Snow::Snow(Vector3 position, Vector3 scale, Renderer* renderer) : Weather(position, scale, renderer)
{
	renderer->SetSnowSpeed(0.1f);
	Draw drawer = Draw(renderer);
	TextureBase* floorTexture = OGLTexture::RGBATextureFromFilename("perlin_noise.png");
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	
	RenderObject* floorPlane = drawer.DrawPatchedPlane(position-Vector3(0,scale.y/2,0),Vector2(scale.x,scale.z), Vector4(1,1,1,1));
	floorPlane->SetShader(new OGLShader("snowVert.glsl", "snowFrag.glsl", "", "snowTCS.glsl", "snowTES.glsl"));
	floorPlane->SetBaseTexture(OGLTexture::RGBATextureFromFilename("perlin_noise.png"));

	snowflakes = new vector<Particle>();
	shader = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "particleShader.glsl");
	
	texture = OGLTexture::RGBATextureFromFilename("snowflake.png");

	mesh = new OGLMesh();
	mesh->SetVertexPositions({ Vector3{0,0,0} });
	mesh->SetVertexColours({ Vector4(1,1,1,1) });
	mesh->SetPrimitiveType(NCL::GeometryPrimitive::Points);
	mesh->UploadToGPU();

}

void Snow::Update()
{
	while (rand() % 100 < 70 && snowflakes->size() < 15000){
		Vector3 coords = generateRandomCoord();
		coords.y = position.y + (scale.y/2);
		Vector3 velocity = generateRanomVelocity();
		snowflakes->push_back(Particle(coords,mesh,shader,texture, renderer, velocity));
	}
	for (int i = 0; i < snowflakes->size(); i++) {
		UpdateSnowflake(snowflakes->at(i));
	}
}

void Snow::UpdateSnowflake(Particle& p) {
	p.Update();
	if (p.GetPosition().y < position.y - (scale.y/2)) {
		Vector3 newPosition = generateRandomCoord();
		newPosition.y = position.y + (scale.y / 2);
		p.SetVelocity(generateRanomVelocity());
		p.MoveTo(newPosition);
	}
}

Vector3 Snow::generateRandomCoord() {
	float x = (rand() % (int)(scale.x)) - (0.5 * (int)(scale.x)) + position.x;
	float y = (rand() % (int)(scale.y)) - (0.5 * (int)(scale.y)) + position.y;
	float z = (rand() % (int)(scale.z)) - (0.5 * (int)(scale.z)) + position.z;
	return Vector3(x, y, z);
}

Vector3 Snow::generateRanomVelocity()
{
	float x = (rand() % 100) / 5000.0f - 0.01f;
	float y = (rand() % 100) / 5000.0f - 0.01f;
	float z = (rand() % 100) / 5000.0f - 0.01f;

	return Vector3(x, y, z) + Vector3(0.01f,-0.05f,0);
}