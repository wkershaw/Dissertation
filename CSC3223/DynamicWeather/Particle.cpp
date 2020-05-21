#include "Particle.h"
Particle::Particle(Vector3 position, OGLMesh* mesh, OGLShader* shader, TextureBase* texture, Renderer* renderer, Vector3 velocity)
{
	this->velocity = velocity;
	this->position = position;
	this->renderer = renderer;
	this->mesh = mesh;
	this->shader = shader;
	object = new RenderObject(mesh, Matrix4::Translation(position));
	object->SetShader(shader);
	object->SetBaseTexture(texture);
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

void Particle::SetVelocity(Vector3 newVelocity) {
	velocity = newVelocity;
}

float Particle::GetSize()
{
	return object->GetParticleSize();
}

void Particle::SetSize(float newSize)
{
	object->SetParticleSize(newSize);
}

Vector3 Particle::GetPosition()
{
	return position;
}

Vector3 Particle::GetVelocity()
{
	return velocity;
}
