#include "Snow.h"

Snow::Snow(Renderer* renderer)
{
	particles = new vector<Particle>();
	this->renderer = renderer;
	this->shader = nullptr;
	OGLShader* shader = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "particleShader.glsl");
	
	mesh = new OGLMesh();
	mesh->SetVertexPositions({ Vector3{0,0,0} });
	mesh->SetVertexColours({ Vector4(1,1,1,1) });
	mesh->SetPrimitiveType(NCL::GeometryPrimitive::Points);
	mesh->UploadToGPU();

}

void Snow::Update()
{
	if (particles->size() < 1000) {
		int toAdd = rand() % 2;
		for (int i = 0; i < toAdd; i++) {
			float x = (((rand() % 100)) / 5.0) - 10;
			float z = (((rand() % 100) / 5.0) - 100);
			particles->push_back(Particle(x, 5, z, mesh,shader));
			renderer->AddRenderObject(particles->back().getObject());
		}
	}
	for (int i = 0; i < particles->size(); i++) {
		if (particles->at(i).getPosition().y < -30) {
			float x = (((rand() % 100)) / 5.0 - 10);
			float z = (((rand() % 100) / 5.0) - 100);
			particles->at(i).MoveTo(x, 5, z);
		}
		else {
			particles->at(i).DisplaceBy(0, -0.1f, 0);
		}

	}
}
