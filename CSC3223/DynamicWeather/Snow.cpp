#include "Snow.h"

Snow::Snow(Renderer* renderer, Vector3 position, Vector3 size, int maxParticles, int rate)
{
	this->renderer = renderer;

	this->position = position;
	this->size = size;
	this->maxParticles = maxParticles;
	this->rate = rate;

	particles = new vector<Particle>();
	snowflakeShader = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "particleShader.glsl");
	
	snowflakeTexture = OGLTexture::RGBATextureFromFilename("snowflake.png");

	mesh = new OGLMesh();
	mesh->SetVertexPositions({ Vector3{0,0,0} });
	mesh->SetVertexColours({ Vector4(1,1,1,1) });
	mesh->SetPrimitiveType(NCL::GeometryPrimitive::Points);
	mesh->UploadToGPU();
}

void Snow::Update()
{
	while (particles->size() < maxParticles && rand() % 1000 < rate) {
		Vector3 coords = generateRandomCoord();
		coords.y = position.y + (size.y/2);
		Vector3 velocity = generateRanomVelocity();
		particles->push_back(Particle(coords,velocity,mesh,snowflakeShader,snowflakeTexture, renderer));
	}
	for (int i = 0; i < particles->size(); i++) {
		UpdateParticle(particles->at(i));
	}
}

void Snow::UpdateParticle(Particle& p) {
	p.Update();
	if (p.getPosition().y < position.y-(size.z/2)) {
		Vector3 newPos = generateRandomCoord();
		newPos.y = position.y + (size.y/2);
		p.MoveTo(newPos);
	}
}

Vector3 Snow::generateRandomCoord() {
	float decimal = (rand() % 100) / 200.0f;
	float x = (rand() % (int)size.x) - (0.5 * size.x) + position.x + decimal;
	float y = (rand() % (int)size.y)- (0.5 * size.y) + position.y + decimal;
	float z = (rand() % (int)size.z) - (0.5 * size.z) + position.z + decimal;
	return Vector3(x, y, z);
}

Vector3 Snow::generateRanomVelocity()
{
	//float x = (rand() % 100) / 5000.0f - 0.01f;
	//float y = (rand() % 100) / 5000.0f - 0.01f;
	//float z = (rand() % 100) / 5000.0f - 0.01f;

	//return Vector3(x, y, z) + Vector3(0.01f,-0.05f,0);
	return Vector3(0, -0.05f, 0);
}

