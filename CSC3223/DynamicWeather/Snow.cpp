#include "Snow.h"

Snow::Snow(Renderer* renderer)
{
	this->renderer = renderer;

	position = Vector3(0, 0, -20);
	width = 20;
	depth = 20;
	height = 40;
	resolution = 100.0f;

	particles = new vector<Particle>();
	shader = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "particleShader.glsl");
	
	mesh = new OGLMesh();
	mesh->SetVertexPositions({ Vector3{0,0,0} });
	mesh->SetVertexColours({ Vector4(1,1,1,1) });
	mesh->SetPrimitiveType(NCL::GeometryPrimitive::Points);
	mesh->UploadToGPU();

}

void Snow::Update()
{
	while (particles->size() < 1000 && rand() % 100 < 70) {
		Vector3 coords = generateRandomCoord();
		coords.y = 10;
		Vector3 velocity = generateRanomVelocity();
		particles->push_back(Particle(coords,velocity,mesh,shader, renderer));
	}
	for (int i = 0; i < particles->size(); i++) {
		UpdateParticle(particles->at(i));
	}
}

void Snow::UpdateParticle(Particle& p) {
	p.Update();
	if (p.getPosition().y < -10) {
		Vector3 newPos = generateRandomCoord();
		newPos.y = 10;
		p.MoveTo(newPos);
	}
}

Vector3 Snow::generateRandomCoord() {
	float x = (rand() % width) - (0.5 * width) + position.x;
	float y = (rand() % height) - (0.5 * height) + position.y;
	float z = (rand() % depth) - (0.5 * depth) + position.z;
	return Vector3(x, y, z);
}

Vector3 Snow::generateRanomVelocity()
{
	float x = (rand() % 100) / 2000.0f;
	float y = (rand() % 100) / -1000.0f;
	float z = (rand() % 100) / 2000.0f;
	return Vector3(x, y, z);
}

