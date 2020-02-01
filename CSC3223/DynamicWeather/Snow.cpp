#include "Snow.h"
#include "../../Common/Vector3.h"
#include "RenderObject.cpp"
#include <OGLMesh.h>
#include <OGLShader.h>
#include <OGLTexture.cpp>
#include "Renderer.h"


Snow::Snow(int p, Renderer* r)
{
	particleLimit = p;
	renderer = r;
}

void Snow::Update()
{
	int noToBeAdded = rand() % (particleLimit - particles.size());
	std::cout << noToBeAdded;
	for (int i = 0; i < noToBeAdded; i++) {
		float x = rand() % 10;
		particles.push_back(makeSnowFlake(x,0,-5));
	}
	for (int i = 0; i < particles.size(); i++) {
		SnowFlake s = particles.at(i);
		displaceSnowFlake(0, -1, 0, s);

	}
}

void Snow::moveSnowFlake(float x, float y, float z, SnowFlake s)
{
	s.x = x;
	s.y = y;
	s.z = z;
	s.object->SetTransform(NCL::Maths::Matrix4::Translation(NCL::Maths::Vector3::Vector3(x, y, z)));
}

void Snow::displaceSnowFlake(float dx, float dy, float dz, SnowFlake s)
{
	s.x += dx;
	s.y += dy;
	s.z += dz;
	s.object->SetTransform(NCL::Maths::Matrix4::Translation(NCL::Maths::Vector3::Vector3(s.x, s.y, s.z)));
}

SnowFlake Snow::makeSnowFlake(float x, float y, float z)
{
	SnowFlake s;
	s.x = x;
	s.y = y;
	s.z = z;


	OGLMesh* snow = new OGLMesh();
	snow->SetVertexPositions({ Vector3(0,0,0) });
	snow->SetVertexColours({ Vector4(1, 1, 1, 1) });
	snow->SetPrimitiveType(GeometryPrimitive::Points);
	snow->UploadToGPU();
	OGLShader* particleShader = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "particleShader.glsl");

	RenderObject* snowObject = new RenderObject(snow, Matrix4::Translation(Vector3(x, y, z)));
	snowObject->SetBaseTexture(OGLTexture::RGBATextureFromFilename("doge.png"));
	snowObject->SetShader(particleShader);
	renderer->AddRenderObject(snowObject);
	
	s.object = snowObject;
	return s;
}
