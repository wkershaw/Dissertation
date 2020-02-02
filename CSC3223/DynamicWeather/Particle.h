#pragma once
#include "RenderObject.h"
#include "../../Common/Vector3.h";
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"

using namespace NCL::CSC3223;
using namespace NCL::Rendering;
class Particle
{
public:
	Particle(float x, float y, float z, OGLMesh* mesh, OGLShader* shader);
	void MoveTo(float x, float y, float z);
	void DisplaceBy(float x, float y, float z);
	RenderObject* getObject();
	Vector3 getPosition();
private:
	float x;
	float y;
	float z;
	RenderObject* object;
	OGLMesh* mesh;
	OGLShader* shader;
};

