#include "Particle.h"


Particle::Particle(float x, float y, float z, OGLMesh* mesh, OGLShader* shader)
{

	this->x = x;
	this->y = y;
	this->z = z;
	this->mesh = mesh;
	this->shader = shader;
	object = new RenderObject(mesh, Matrix4::Translation(Vector3(x,y,z)));
	object->SetShader(shader);

}

void Particle::MoveTo(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	Vector3 newPosition = Vector3(x, y, z);
	object->SetTransform(Matrix4::Translation(newPosition));
}

void Particle::DisplaceBy(float dx, float dy, float dz)
{
	this->x += dx;
	this->y += dy;
	this->z += dz;
	Vector3 newPosition = Vector3(x, y, z);
	object->SetTransform(Matrix4::Translation(newPosition));
}

RenderObject* Particle::getObject()
{
	return object;
}

Vector3 Particle::getPosition()
{
	return Vector3(x,y,z);
}
