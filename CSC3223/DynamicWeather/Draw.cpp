#include "Draw.h"
RenderObject* Draw::DrawPlane(Vector3 position, Vector2 scale, Vector4 colour) {
	OGLMesh* plane = new OGLMesh();
	Vector3 bottomLeft = position + Vector3(scale.x / 2, 0, scale.y / 2);
	Vector3 bottomRight = position + Vector3(-scale.x / 2, 0, scale.y / 2);
	Vector3 topLeft = position + Vector3(scale.x / 2, 0, -scale.y / 2);
	Vector3 topRight = position + Vector3(-scale.x / 2, 0, -scale.y / 2);
	plane->SetVertexPositions({ bottomLeft, bottomRight, topLeft, topRight });
	plane->SetVertexTextureCoords({ Vector2(0,0),Vector2(1,0), Vector2(0,1), Vector2(1,1)});
	plane->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	plane->SetVertexColours({ colour,colour,colour,colour });
	plane->UploadToGPU();
	RenderObject* object = new RenderObject(plane);
	renderer->AddRenderObject(object);
	return object;
}

RenderObject* Draw::DrawPatchedPlane(Vector3 position, Vector2 scale, Vector4 colour) {
	OGLMesh* plane = new OGLMesh();
	Vector3 bottomLeft = position + Vector3(scale.x / 2, 0, scale.y / 2);
	Vector3 bottomRight = position + Vector3(-scale.x / 2, 0, scale.y / 2);
	Vector3 topLeft = position + Vector3(scale.x / 2, 0, -scale.y / 2);
	Vector3 topRight = position + Vector3(-scale.x / 2, 0, -scale.y / 2);
	plane->SetVertexPositions({ bottomLeft, bottomRight, topLeft, topRight });
	plane->SetVertexTextureCoords({ Vector2(0,0),Vector2(1,0), Vector2(0,1), Vector2(1,1) });
	plane->SetPrimitiveType(GeometryPrimitive::Patches);
	plane->SetVertexColours({ colour,colour,colour,colour });
	plane->UploadToGPU();
	RenderObject* object = new RenderObject(plane);
	renderer->AddRenderObject(object);
	return object;
}

RenderObject* Draw::DrawCuboid(Vector3 position, Vector3 scale, Vector4 colour) {
	OGLMesh* cuboid = new OGLMesh("Cube.msh");
	cuboid->SetPrimitiveType(GeometryPrimitive::Triangles);
	vector<Vector2> textureCoords = {
		Vector2(1,1),Vector2(1,0),Vector2(0,0),Vector2(0,0),Vector2(0,1),Vector2(1,1),
	};
	vector<Vector4> colourCoords = vector<Vector4>();
	for (int i = 0; i < cuboid->GetVertexCount(); i++) {
		colourCoords.emplace_back(colour);
	}
	cuboid->SetVertexColours(colourCoords);
	cuboid->SetVertexTextureCoords(textureCoords);
	cuboid->UploadToGPU();
	RenderObject* object = new RenderObject(cuboid, Matrix4::Translation(position));
	object->SetTransform(object->GetTransform() * Matrix4::Scale(scale));
	renderer->AddRenderObject(object);
	return object;
	}
