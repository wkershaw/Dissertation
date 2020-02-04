#include "Particle.h"
Particle::Particle(Vector3 position,Vector3 velocity, OGLMesh* mesh, OGLShader* shader, Renderer* renderer)
{
	this->velocity = velocity;
	this->position = position;
	this->renderer = renderer;
	this->mesh = mesh;
	this->shader = shader;
	object = new RenderObject(mesh, Matrix4::Translation(position));
	object->SetShader(shader);
	renderer->AddRenderObject(object);

}

void Particle::MoveTo(Vector3 newPosition)
{
	position = newPosition;
	object->SetTransform(Matrix4::Translation(newPosition));
}

void Particle::DisplaceBy(Vector3 displacment)
{
	position += displacment;
	object->SetTransform(Matrix4::Translation(position));
}

void Particle::Update() {
	DisplaceBy(velocity);
}

Vector3 Particle::getPosition()
{
	return position;
}
