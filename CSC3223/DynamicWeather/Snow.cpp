#include "Snow.h"

void DrawPlane(Renderer* renderer, float width, float depth, float height, Vector3 position, TextureBase* texture) {

	float halfWidth = width / 2.0f;
	float halfDepth = depth / 2.0f;


	OGLMesh* floor = new OGLMesh();
	floor->SetVertexPositions({ Vector3(-halfWidth,0,-halfDepth),Vector3(halfWidth,0,-halfDepth), Vector3(-halfWidth,0,halfDepth), Vector3(halfWidth,0,halfDepth) });
	floor->SetVertexTextureCoords({ Vector2(0,0),Vector2(1,0), Vector2(0,1), Vector2(1,1), });
	floor->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	Vector4 floorColour = Vector4(1, 1, 1, 1);
	floor->SetVertexColours({ floorColour,floorColour,floorColour,floorColour });
	floor->UploadToGPU();
	RenderObject* o = new RenderObject(floor, Matrix4::Translation(Vector3(position.x, position.y - (depth / 2), position.z)));
	o->SetBaseTexture(texture);
	renderer->AddRenderObject(o);
}

Snow::Snow(Renderer* renderer)
{
	this->renderer = renderer;
	position = Vector3(0, 0, -20);
	width = 20;
	depth = 20;
	height = 40;
	resolution = 100.0f;

	TextureBase* floorTexture = OGLTexture::RGBATextureFromFilename("snowflake.png");
	DrawPlane(renderer, width, depth, height, position, floorTexture);

	particles = new vector<Particle>();
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
	while (rand() % 100 < 70) {
		Vector3 coords = generateRandomCoord();
		coords.y = 10;
		Vector3 velocity = generateRanomVelocity();
		particles->push_back(Particle(coords,mesh,shader,texture, renderer, velocity));
	}
	for (int i = 0; i < particles->size(); i++) {
		UpdateParticle(particles->at(i));
	}
}

void Snow::UpdateParticle(Particle& p) {
	p.Update();
	if (p.getPosition().y < position.y - (depth/2)) {
		p.SetVelocity(Vector3(0, 0, 0));
		Vector3 newPosition = p.getPosition();
		newPosition.y = position.y - (depth / 2);
		p.MoveTo(newPosition);
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
	float x = (rand() % 100) / 5000.0f - 0.01f;
	float y = (rand() % 100) / 5000.0f - 0.01f;
	float z = (rand() % 100) / 5000.0f - 0.01f;

	return Vector3(x, y, z) + Vector3(0.01f,-0.05f,0);
}