#include "Particle.h"
#include "../../Common/Vector3.h";
#include <OGLMesh.cpp>
#include <OGLShader.cpp>

Particle::Particle(float x, float y, float z)
{

	this->x = x;
	this->y = y;
	this->z = z;

	OGLMesh* snow = new OGLMesh();
	snow->SetVertexPositions({ Vector3{x,y,z} });
	snow->SetVertexColours({ Vector4(1,1,1,1) });
	snow->SetPrimitiveType(GeometryPrimitive::Points);
	snow->UploadToGPU();
	object = new RenderObject(snow);
	OGLShader* shader = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "particleShader.glsl");
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
