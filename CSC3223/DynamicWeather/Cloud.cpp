#include "Cloud.h"

Cloud::Cloud(Vector3 position, Vector3 scale, Renderer* renderer) : Weather(position, scale, renderer) {
	particles = new vector<Particle>();
	shader = new OGLShader("RasterisationVert.glsl", "RasterisationFrag.glsl", "particleShader.glsl");
	texture0 = OGLTexture::RGBATextureFromFilename("cloud.png");
	texture1 = OGLTexture::RGBATextureFromFilename("cloud1.png");
	texture2 = OGLTexture::RGBATextureFromFilename("cloud2.png");
	OGLMesh* cloudPoint = new OGLMesh();
	cloudPoint->SetVertexPositions({ Vector3(0,0,0) });
	cloudPoint->SetPrimitiveType(GeometryPrimitive::Points);
	cloudPoint->SetVertexColours({ Vector4(1,1,1,1) });
	cloudPoint->UploadToGPU();

	for (int i = 0; i < 4; i++) {
		Vector3 pointPosition = Vector3(
			(rand() % (int)(scale.x)*100) / 100.0f + position.x,
			(rand() % (int)(scale.y)*100) / 100.0f + position.y,
			position.z + (i * 0.1f)
		);
		Particle* p;
		int cloudTex = rand() % 100;
		if (cloudTex < 10) {
			p = new Particle(pointPosition, cloudPoint, shader, texture0, renderer);
		}
		else if (cloudTex < 20) {
			p = new Particle(pointPosition, cloudPoint, shader, texture1, renderer);
		}
		else {
			p = new Particle(pointPosition, cloudPoint, shader, texture2, renderer);
		}
		p->SetSize(5);
		particles->push_back(*p);
	}

}